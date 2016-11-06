#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "mooglpf.hpp"
#include "mooglpf_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "mooglpf_gui.hpp"

MoogLPFGUI::MoogLPFGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage(new VBox(true));


    MyBox *p_gainFrame = manage(new MyBox("Gain", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialInputGain = new LabeledDial("Input", -15, 15, NORMAL, 0.01);
    m_dialInputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_inputGain), mem_fun(*m_dialInputGain,  &LabeledDial::get_value)));
    p_gainFrame->pack_start(*m_dialInputGain);

	m_dialOutputGain = new LabeledDial("Output", -15, 15, NORMAL, 0.01);
    m_dialOutputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_outputGain), mem_fun(*m_dialOutputGain,  &LabeledDial::get_value)));
    p_gainFrame->pack_start(*m_dialOutputGain);

    p_mainWidget->pack_start(*p_gainFrame);


    MyBox *p_freqFrame = manage(new MyBox("Frequency", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialFrequency = new LabeledDial("Frequency", -6, 6, NORMAL, 0.01);
    m_dialFrequency->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_frequency), mem_fun(*m_dialFrequency,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialFrequency);

	m_dialExpFMGain = new LabeledDial("Exp FM Gain", 0, 10, LOG, 0.001);
    m_dialExpFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_expFMGain), mem_fun(*m_dialExpFMGain,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_dialExpFMGain);

    p_mainWidget->pack_start(*p_freqFrame);


    MyBox *p_resonanceFrame = manage(new MyBox("Resonance", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_dialResonance = new LabeledDial("Resonance", 0, 1, NORMAL, 0.01);
    m_dialResonance->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_resonance), mem_fun(*m_dialResonance,  &LabeledDial::get_value)));
    p_resonanceFrame->pack_start(*m_dialResonance);

	m_dialResonanceGain = new LabeledDial("Gain", 0, 1, NORMAL, 0.01);
    m_dialResonanceGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &MoogLPFGUI::write_control), p_resonanceGain), mem_fun(*m_dialResonanceGain,  &LabeledDial::get_value)));
    p_resonanceFrame->pack_start(*m_dialResonanceGain);

    p_mainWidget->pack_start(*p_resonanceFrame);


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
    case p_expFMGain:
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
