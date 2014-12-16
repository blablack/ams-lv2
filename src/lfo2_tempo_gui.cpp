#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "lfo2_tempo.hpp"
#include "lfo2_tempo_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "lfo2_tempo_gui.hpp"

Lfo2TempoGUI::Lfo2TempoGUI(const std::string& URI)
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
    m_comboWaveForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &Lfo2TempoGUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number)));
    p_labelWaveForm->pack_start(*m_comboWaveForm);

    p_mainWidget->pack_start(*p_labelWaveForm);


    MyBox *p_freqFrame = manage(new MyBox("Wave", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialTempo = new LabeledDial("Tempo", 1, 320, NORMAL, 1);
    m_dialTempo->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Lfo2TempoGUI::write_control), p_tempo), mem_fun(*m_dialTempo, &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialTempo);

	m_dialTempoMultiplier = new LabeledDial("Multiplier", 0.0078125, 128, MULTIPLIER, 0.0078125);
    m_dialTempoMultiplier->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Lfo2TempoGUI::write_control), p_tempoMultiplier), mem_fun(*m_dialTempoMultiplier, &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialTempoMultiplier);

	m_dialPhi0 = new LabeledDial("Phi0", 0, 6.28, NORMAL, 0.01);
    m_dialPhi0->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &Lfo2TempoGUI::write_control), p_phi0), mem_fun(*m_dialPhi0, &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialPhi0);

    p_mainWidget->pack_start(*p_freqFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Lfo2TempoGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_waveFormValue;
    float p_multiplierValue;

    switch(port)
    {
    case p_waveForm:
        p_waveFormValue = (int) (*static_cast<const float*> (buffer));
        if (p_waveFormValue >= 0 && p_waveFormValue <= 5)
            m_comboWaveForm->set_active((int) p_waveFormValue);
        break;
    case p_tempo:
        m_dialTempo->set_value(*static_cast<const float*> (buffer));
        break;
    case p_tempoMultiplier:
        p_multiplierValue = (float) (*static_cast<const float*> (buffer));
        if(p_multiplierValue <= 0.0078125)
            m_dialTempoMultiplier->set_value(0.0078125);
        else if(p_multiplierValue <= 0.015625)
            m_dialTempoMultiplier->set_value(0.015625);
        else if(p_multiplierValue <= 0.03125)
            m_dialTempoMultiplier->set_value(0.03125);
        else if(p_multiplierValue <= 0.0625)
            m_dialTempoMultiplier->set_value(0.0625);
        else if(p_multiplierValue <= 0.125)
            m_dialTempoMultiplier->set_value(0.125);
        else if(p_multiplierValue <= 0.25)
            m_dialTempoMultiplier->set_value(0.25);
        else if(p_multiplierValue <= 0.5)
            m_dialTempoMultiplier->set_value(0.5);
        else if(p_multiplierValue <= 1)
            m_dialTempoMultiplier->set_value(1);
        else if(p_multiplierValue <= 2)
            m_dialTempoMultiplier->set_value(2);
        else if(p_multiplierValue <= 4)
            m_dialTempoMultiplier->set_value(4);
        else if(p_multiplierValue <= 8)
            m_dialTempoMultiplier->set_value(8);
        else if(p_multiplierValue <= 16)
            m_dialTempoMultiplier->set_value(16);
        else if(p_multiplierValue <= 32)
            m_dialTempoMultiplier->set_value(32);
        else if(p_multiplierValue <= 64)
            m_dialTempoMultiplier->set_value(64);
        else if(p_multiplierValue > 64)
            m_dialTempoMultiplier->set_value(128);
        break;
    case p_phi0:
        m_dialPhi0->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = Lfo2TempoGUI::register_class("http://github.com/blablack/ams-lv2/lfo2_tempo/gui");
