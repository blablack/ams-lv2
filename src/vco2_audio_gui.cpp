#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vco2_audio_gui.hpp"
#include "vco2_audio.hpp"
#include "dial.hpp"

Vco2AudioGUI::Vco2AudioGUI(const char* plugin_uri)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);



    VBox *p_mainWidget = manage(new VBox(false, 5));



    Label *p_labeWaveForm = manage (new Label("Wave Form"));
    p_mainWidget->pack_start(*p_labeWaveForm);

    m_comboWaveForm = manage (new ComboBoxText());
    m_comboWaveForm->append_text("Sine");
    m_comboWaveForm->append_text("Triangle");
    m_comboWaveForm->append_text("Sawtooth");
    m_comboWaveForm->append_text("Rectangle");
    m_comboWaveForm->append_text("Aux Saw 1");
    m_comboWaveForm->append_text("Aux Saw 2");
    m_comboWaveForm->append_text("Aux Saw 3");

    m_comboWaveForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &Vco2AudioGUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number)));
    m_comboWaveForm->signal_changed().connect(mem_fun(*this, &Vco2AudioGUI::get_waveform));
    p_mainWidget->pack_start(*m_comboWaveForm);



    Frame *p_freqFrame = manage(new Frame("Frequency"));
    //p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
    HBox *p_freqBox = manage(new HBox(true));

    m_scaleOctave = new LabeledDial("Octave", p_octave, 0, 6, NORMAL, 1, 0);
    m_scaleOctave->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_octave), mem_fun(*m_scaleOctave,  &LabeledDial::get_value)));
    p_freqBox->pack_start(*m_scaleOctave);

    m_scaleTune = new LabeledDial("Tune", p_tune, 0, 1, LOG, 0.0001, 4);
    m_scaleTune->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_tune), mem_fun(*m_scaleTune,  &LabeledDial::get_value)));
    p_freqBox->pack_start(*m_scaleTune);

    m_scaleSemitone = new LabeledDial("Semitone", p_semitone, 0, 12, NORMAL, 1, 0);
    m_scaleSemitone->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_semitone), mem_fun(*m_scaleSemitone,  &LabeledDial::get_value)));
    p_freqBox->pack_start(*m_scaleSemitone);

    p_freqFrame->add(*p_freqBox);
    p_mainWidget->pack_start(*p_freqFrame);



    Frame *p_pwpFrame = manage(new Frame("Pulse Width / Phase"));
    //p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
    HBox *p_pwpBox = manage(new HBox(true));

    m_scalePW = new LabeledDial("PW", p_pw0, 0.1, 0.9, NORMAL, 0.001, 3);
    m_scalePW->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_pw0), mem_fun(*m_scalePW,  &LabeledDial::get_value)));
    p_pwpBox->pack_start(*m_scalePW);

    m_scalePWGain = new LabeledDial("PW Gain", p_pwGain, 0, 1, LOG, 0.0001, 4);
    m_scalePWGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_pwGain), mem_fun(*m_scalePWGain,  &LabeledDial::get_value)));
    p_pwpBox->pack_start(*m_scalePWGain);

    m_scaleEdge = new LabeledDial("Edge", p_edge, 1, 10, NORMAL, 0.05, 2);
    m_scaleEdge->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_edge), mem_fun(*m_scaleEdge,  &LabeledDial::get_value)));
    p_pwpBox->pack_start(*m_scaleEdge);

    m_scalePhi0 = new LabeledDial("Phi0", p_phi0, 0, 6.28, LOG, 0.0001, 4);
    m_scalePhi0->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_phi0), mem_fun(*m_scalePhi0,  &LabeledDial::get_value)));
    p_pwpBox->pack_start(*m_scalePhi0);

    p_pwpFrame->add(*p_pwpBox);
    p_mainWidget->pack_start(*p_pwpFrame);



    Frame *p_modulationFrame = manage(new Frame("Modulation"));
    //p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
    HBox *p_modulationBox = manage(new HBox(true));

    m_scaleExpFMGain = new LabeledDial("Exp FM Gain", p_expFMGain, 0, 10, LOG, 0.001, 3);
    m_scaleExpFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_expFMGain), mem_fun(*m_scaleExpFMGain,  &LabeledDial::get_value)));
    p_modulationBox->pack_start(*m_scaleExpFMGain);

    m_scaleLinFMGain = new LabeledDial("Lin FM Gain", p_linFMGain, 0, 10, LOG, 0.001, 3);
    m_scaleLinFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Vco2AudioGUI::write_control), p_linFMGain), mem_fun(*m_scaleLinFMGain,  &LabeledDial::get_value)));
    p_modulationBox->pack_start(*m_scaleLinFMGain);

    p_modulationFrame->add(*p_modulationBox);
    p_mainWidget->pack_start(*p_modulationFrame);



    p_mainWidget->set_size_request(260, 360);

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Vco2AudioGUI::get_waveform()
{
    if(m_comboWaveForm->get_active_row_number() == 2 || m_comboWaveForm->get_active_row_number() == 3)
    {
        m_scalePW->enable();
        m_scalePWGain->enable();
        m_scaleEdge->enable();
    }
    else
    {
        m_scalePW->disable();
        m_scalePWGain->disable();
        m_scaleEdge->disable();
    }
}

void Vco2AudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_waveFormValue;

    switch(port)
    {
    case p_waveForm:
        p_waveFormValue = (int) (*static_cast<const float*> (buffer));
        if (p_waveFormValue >= 0 && p_waveFormValue <= 6)
        {
            m_comboWaveForm->set_active((int) p_waveFormValue);
            if(p_waveFormValue == 2 || p_waveFormValue == 3)
            {
                m_scalePW->enable();
                m_scalePWGain->enable();
                m_scaleEdge->enable();
            }
            else
            {
                m_scalePW->disable();
                m_scalePWGain->disable();
                m_scaleEdge->disable();
            }
        }
        break;
    case p_octave:
        m_scaleOctave->set_value(*static_cast<const float*> (buffer));
        break;
    case p_tune:
        m_scaleTune->set_value(*static_cast<const float*> (buffer));
        break;
    case p_semitone:
        m_scaleSemitone->set_value(*static_cast<const float*> (buffer));
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

static int _ = Vco2AudioGUI::register_class("http://github.com/blablack/ams-lv2/vco2_audio/gui");
