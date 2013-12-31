#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "mooglpf_gui.hpp"
#include "mooglpf.hpp"
#include "dial.hpp"

MoogLPFGUI::MoogLPFGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);



    VBox *p_mainWidget = manage(new VBox(true, 5));



    Frame *p_gainFrame = manage(new Frame("Gain"));
    HBox *p_gainBox = manage(new HBox(false));

    m_dialInputGain = new LabeledDial("Input Gain", p_inputGain, -60, 10, NORMAL, 0.01, 2);
    m_dialInputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_inputGain), mem_fun(*m_dialInputGain,  &LabeledDial::get_value)));
    p_gainBox->pack_start(*m_dialInputGain);

    m_dialOutputGain = new LabeledDial("Output Gain", p_outputGain, -15, 15, NORMAL, 0.01, 2);
    m_dialOutputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_outputGain), mem_fun(*m_dialOutputGain,  &LabeledDial::get_value)));
    p_gainBox->pack_start(*m_dialOutputGain);

    p_gainFrame->add(*p_gainBox);
    p_mainWidget->pack_start(*p_gainFrame);



    Frame *p_freqFrame = manage(new Frame("Frequency"));
    HBox *p_freqBox = manage(new HBox(false));

    m_dialFrequency = new LabeledDial("Frequency", p_frequency, -6, 6, NORMAL, 0.01, 2);
    m_dialFrequency->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_frequency), mem_fun(*m_dialFrequency,  &LabeledDial::get_value)));
    p_freqBox->pack_start(*m_dialFrequency);

    m_dialExpFMGain = new LabeledDial("Exp FM Gain", p_expfmgain, 0, 10, LOG, 0.001, 3);
    m_dialExpFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_expfmgain), mem_fun(*m_dialExpFMGain,  &LabeledDial::get_value)));
    p_freqBox->pack_start(*m_dialExpFMGain);

    p_freqFrame->add(*p_freqBox);
    p_mainWidget->pack_start(*p_freqFrame);



    Frame *p_resonanceFrame = manage(new Frame("Resonance"));
    HBox *p_resonanceBox = manage(new HBox(false));

    m_dialResonance = new LabeledDial("Resonance", p_resonance, 0, 1, NORMAL, 0.01, 2);
    m_dialResonance->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_resonance), mem_fun(*m_dialResonance,  &LabeledDial::get_value)));
    p_resonanceBox->pack_start(*m_dialResonance);

    m_dialResonanceGain = new LabeledDial("ResonanceGain", p_resonanceGain, 0, 1, NORMAL, 0.01, 2);
    m_dialResonanceGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_resonanceGain), mem_fun(*m_dialResonanceGain,  &LabeledDial::get_value)));
    p_resonanceBox->pack_start(*m_dialResonanceGain);

    p_resonanceFrame->add(*p_resonanceBox);
    p_mainWidget->pack_start(*p_resonanceFrame);



    p_mainWidget->set_size_request(200, 300);

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void MoogLPFGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_inputGain:
        m_dialInputGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_outputGain:
        m_dialOutputGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_frequency:
        m_dialFrequency->set_value(*static_cast<const float*> (buffer));
        break;
    case p_expfmgain:
        m_dialExpFMGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_resonance:
        m_dialResonance->set_value(*static_cast<const float*> (buffer));
        break;
    case p_resonanceGain:
        m_dialResonanceGain->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = MoogLPFGUI::register_class("http://github.com/blablack/ams-lv2/mooglpf/gui");
