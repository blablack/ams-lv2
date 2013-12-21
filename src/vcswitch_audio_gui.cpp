#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcswitch_audio_gui.hpp"
#include "vcswitch_audio.hpp"
#include "dial.hpp"

VCSwitchAudioGUI::VCSwitchAudioGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotSwitchLevel = compose(bind<0>(mem_fun(*this, &VCSwitchAudioGUI::write_control), p_switchlevel), mem_fun(*this,  &VCSwitchAudioGUI::get_switchLevel));
	m_dialSwitchLevel = new LabeledDial("Switch Level", p_slotSwitchLevel, p_switchlevel, 0, 10, LOG, 0.0001, 4);
	p_background->add(*m_dialSwitchLevel);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float VCSwitchAudioGUI::get_switchLevel() { return m_dialSwitchLevel->get_value(); }

void VCSwitchAudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_switchlevel)
	{
		m_dialSwitchLevel->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = VCSwitchAudioGUI::register_class("http://github.com/blablack/ams-lv2/vcswitch_audio/gui");
