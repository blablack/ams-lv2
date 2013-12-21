#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "delay_gui.hpp"
#include "delay.hpp"
#include "dial.hpp"

DelayGUI::DelayGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotDelay = compose(bind<0>(mem_fun(*this, &DelayGUI::write_control), p_delay), mem_fun(*this,  &DelayGUI::get_delay));
	m_dialDelay = new LabeledDial("Delay", p_slotDelay, p_delay, 0, 10, LOG, 0.001, 3);
	p_background->add(*m_dialDelay);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float DelayGUI::get_delay() { return m_dialDelay->get_value(); }

void DelayGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_delay)
	{
		m_dialDelay->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = DelayGUI::register_class("http://github.com/blablack/ams-lv2/delay/gui");
