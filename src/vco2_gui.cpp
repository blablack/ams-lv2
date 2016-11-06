#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "vco2.hpp"
#include "vco2_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vco2_gui.hpp"

Vco2GUI::Vco2GUI(const char* plugin_uri)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage(new VBox(false));


    MyBox *p_waveFormFrame = manage (new MyBox("Wave Form", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboWaveForm = manage (new ComboBoxText());
    m_comboWaveForm->append_text("Sine");
    m_comboWaveForm->append_text("Triangle");
    m_comboWaveForm->append_text("Sawtooth");
    m_comboWaveForm->append_text("Rectangle");
    m_comboWaveForm->append_text("Aux Saw 1");
    m_comboWaveForm->append_text("Aux Saw 2");
    m_comboWaveForm->append_text("Aux Saw 3");
    //m_comboWaveForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &Vco2GUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number)));
    m_comboWaveForm->signal_changed().connect(mem_fun(*this, &Vco2GUI::get_waveform));

    p_waveFormFrame->pack_start(*m_comboWaveForm);
    p_mainWidget->pack_start(*p_waveFormFrame);


    MyBox *p_freqFrame = manage(new MyBox("Frequency", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleOctave = new LabeledDial("Octave", 0, 6, NORMAL, 1);
    m_scaleOctave->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_octave), mem_fun(*m_scaleOctave,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleOctave);

	m_scaleTune = new LabeledDial("Tune", -1, 1, NORMAL, 0.001);
    m_scaleTune->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_tune), mem_fun(*m_scaleTune,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleTune);

	m_scaleHarmonic = new LabeledDial("Harmonic", 1, 16, NORMAL, 1);
    m_scaleHarmonic->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_harmonic), mem_fun(*m_scaleHarmonic,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleHarmonic);

	m_scaleSubharmonic = new LabeledDial("Subharmonic", 1, 16, NORMAL, 1);
    m_scaleSubharmonic->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_subharmonic), mem_fun(*m_scaleSubharmonic,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleSubharmonic);

    p_mainWidget->pack_start(*p_freqFrame);


    MyBox *p_pwpFrame = manage(new MyBox("Pulse Width / Phase", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scalePW = new LabeledDial("PW", 0.1, 0.9, NORMAL, 0.001);
    m_scalePW->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_pw0), mem_fun(*m_scalePW,  &LabeledDial::get_value)));
    p_pwpFrame->pack_start(*m_scalePW);

	m_scalePWGain = new LabeledDial("PW Gain", 0, 1, LOG, 0.0001);
    m_scalePWGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_pwGain), mem_fun(*m_scalePWGain,  &LabeledDial::get_value)));
    p_pwpFrame->pack_start(*m_scalePWGain);

	m_scaleEdge = new LabeledDial("Edge", 1, 10, NORMAL, 0.05);
    m_scaleEdge->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_edge), mem_fun(*m_scaleEdge,  &LabeledDial::get_value)));
    p_pwpFrame->pack_start(*m_scaleEdge);

	m_scalePhi0 = new LabeledDial("Phi0",  0, 6.28, LOG, 0.0001);
    m_scalePhi0->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_phi0), mem_fun(*m_scalePhi0,  &LabeledDial::get_value)));
    p_pwpFrame->pack_start(*m_scalePhi0);

    p_mainWidget->pack_start(*p_pwpFrame);


    MyBox *p_modulationFrame = manage(new MyBox("Modulation", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleExpFMGain = new LabeledDial("Exp FM Gain", 0, 10, LOG, 0.001);
    m_scaleExpFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_expFMGain), mem_fun(*m_scaleExpFMGain,  &LabeledDial::get_value)));
    p_modulationFrame->pack_start(*m_scaleExpFMGain);

	m_scaleLinFMGain = new LabeledDial("Lin FM Gain", 0, 10, LOG, 0.001);
    m_scaleLinFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_linFMGain), mem_fun(*m_scaleLinFMGain,  &LabeledDial::get_value)));
    p_modulationFrame->pack_start(*m_scaleLinFMGain);

    p_mainWidget->pack_start(*p_modulationFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Vco2GUI::deactive_gui_parts()
{
    if(m_comboWaveForm->get_active_row_number() == 2 || m_comboWaveForm->get_active_row_number() == 3)
        m_scaleEdge->enable();
    else
        m_scaleEdge->disable();

    if(m_comboWaveForm->get_active_row_number() == 3)
    {
        m_scalePW->enable();
        m_scalePWGain->enable();
    }
    else
    {
        m_scalePW->disable();
        m_scalePWGain->disable();
    }
}

void Vco2GUI::get_waveform()
{
    deactive_gui_parts();
    this->write_control(p_waveForm, m_comboWaveForm->get_active_row_number());
}

void Vco2GUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_waveFormValue;

    switch(port)
    {
    case p_waveForm:
        p_waveFormValue = (int) (*static_cast<const float*> (buffer));
        if (p_waveFormValue >= 0 && p_waveFormValue <= 6)
        {
            m_comboWaveForm->set_active((int) p_waveFormValue);
            deactive_gui_parts();
        }
        break;
    case p_octave:
        m_scaleOctave->set_value(*static_cast<const float*> (buffer));
        break;
    case p_tune:
        m_scaleTune->set_value(*static_cast<const float*> (buffer));
        break;
    case p_harmonic:
        m_scaleHarmonic->set_value(*static_cast<const float*> (buffer));
        break;
    case p_subharmonic:
        m_scaleSubharmonic->set_value(*static_cast<const float*> (buffer));
        break;
    case p_pw0:
        m_scalePW->set_value(*static_cast<const float*> (buffer));
        break;
    case p_pwGain:
        m_scalePWGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_edge:
        m_scaleEdge->set_value(*static_cast<const float*> (buffer));
        break;
    case p_phi0:
        m_scalePhi0->set_value(*static_cast<const float*> (buffer));
        break;
    case p_expFMGain:
        m_scaleExpFMGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_linFMGain:
        m_scaleLinFMGain->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = Vco2GUI::register_class("http://github.com/blablack/ams-lv2/vco2/gui");
