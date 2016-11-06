#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "delay.hpp"
#include "delay_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "delay_gui.hpp"

DelayGUI::DelayGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	m_dialDelay = new LabeledDial("Delay", 0, 10, LOG, 0.001);
	m_dialDelay->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &DelayGUI::write_control), p_delay), mem_fun(*m_dialDelay,  &LabeledDial::get_value)));

    Alignment* p_align = new Alignment(0.5, 0.5, 0, 0);

    p_align->add(*m_dialDelay);
	p_background->add(*p_align);
	add(*p_background);

	Gtk::manage(p_background);
}

void DelayGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_delay)
		m_dialDelay->set_value(*static_cast<const float*> (buffer));
}

static int _ = DelayGUI::register_class("http://github.com/blablack/ams-lv2/delay/gui");
