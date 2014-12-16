#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "ringmodulator.hpp"
#include "ringmodulator_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "ringmodulator_gui.hpp"

RingModulatorGUI::RingModulatorGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	m_dialGain = new LabeledDial("Gain", -10, 10, NORMAL, 0.01);
    m_dialGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &RingModulatorGUI::write_control), p_gain), mem_fun(*m_dialGain,  &LabeledDial::get_value)));

    Alignment* p_align = new Alignment(0.5, 0.5, 0, 0);

    p_align->add(*m_dialGain);
	p_background->add(*p_align);
    add(*p_background);

    Gtk::manage(p_background);
}

void RingModulatorGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    if (port == p_gain)
        m_dialGain->set_value(*static_cast<const float*> (buffer));
}

static int _ = RingModulatorGUI::register_class("http://github.com/blablack/ams-lv2/ringmodulator/gui");
