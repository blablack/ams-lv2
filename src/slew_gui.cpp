#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "slew_gui.hpp"
#include "slew.hpp"
#include "dial.hpp"

SlewGUI::SlewGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	slot<void> p_slotTimeUp = compose(bind<0>(mem_fun(*this, &SlewGUI::write_control), p_timeUp), mem_fun(*this,  &SlewGUI::get_timeUp));
	m_dialTimeUp = new LabeledDial("Time Up", p_slotTimeUp, p_timeUp, 0, 10, NORMAL, 0.1, 1);
	p_mainWidget->pack_start(*m_dialTimeUp);

	slot<void> p_slotTimeDown = compose(bind<0>(mem_fun(*this, &SlewGUI::write_control), p_timeDown), mem_fun(*this, &SlewGUI::get_timeDown));
	m_dialTimeDown = new LabeledDial("Time Down", p_slotTimeDown, p_timeDown,0, 10, NORMAL, 0.1, 1);
	p_mainWidget->pack_start(*m_dialTimeDown);

	p_mainWidget->set_size_request(256, 320);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float SlewGUI::get_timeUp() { return m_dialTimeUp->get_value(); }
float SlewGUI::get_timeDown() { return m_dialTimeDown->get_value(); }

void SlewGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_timeUp)
	{
		m_dialTimeUp->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_timeDown)
	{
		m_dialTimeDown->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = SlewGUI::register_class("http://github.com/blablack/ams.lv2/slew/gui");
