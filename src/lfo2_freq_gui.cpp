#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "lfo2_freq.hpp"
#include "lfo2_freq_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "lfo2_freq_gui.hpp"

Lfo2FreqGUI::Lfo2FreqGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    MyBox *p_labelWaveForm = manage (new MyBox("Wave Form", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboWaveForm = manage (new ComboBoxText());
    m_comboWaveForm->append_text("Sine");
    m_comboWaveForm->append_text("Triangle");
    m_comboWaveForm->append_text("Sawtooth Up");
    m_comboWaveForm->append_text("Sawtooth Down");
    m_comboWaveForm->append_text("Rectangle");
    m_comboWaveForm->append_text("S & H");
    m_comboWaveForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &Lfo2FreqGUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number)));
    p_labelWaveForm->pack_start(*m_comboWaveForm);

    p_mainWidget->pack_start(*p_labelWaveForm);


    MyBox *p_freqFrame = manage(new MyBox("Wave", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialTempo = new LabeledDial("Freq", 0.0001, 100, LOG, 0.001);
    m_dialTempo->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Lfo2FreqGUI::write_control), p_freq), mem_fun(*m_dialTempo, &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialTempo);

	m_dialPhi0 = new LabeledDial("Phi0", 0, 6.28, NORMAL, 0.01);
    m_dialPhi0->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &Lfo2FreqGUI::write_control), p_phi0), mem_fun(*m_dialPhi0, &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialPhi0);

    p_mainWidget->pack_start(*p_freqFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Lfo2FreqGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_waveFormValue;
    switch(port)
    {
    case p_waveForm:
        p_waveFormValue = (int) (*static_cast<const float*> (buffer));
        if (p_waveFormValue >= 0 && p_waveFormValue <= 5)
            m_comboWaveForm->set_active((int) p_waveFormValue);
        break;
    case p_freq:
        m_dialTempo->set_value(*static_cast<const float*> (buffer));
        break;
    case p_phi0:
        m_dialPhi0->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = Lfo2FreqGUI::register_class("http://github.com/blablack/ams-lv2/lfo2_freq/gui");
