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

	m_dialSwitchLevel = new LabeledDial("Switch Level", p_switchlevel, 0, 10, LOG, 0.0001, 4);
	m_dialSwitchLevel->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCSwitchAudioGUI::write_control), p_switchlevel), mem_fun(*m_dialSwitchLevel,  &LabeledDial::get_value)));

    Alignment* p_align = new Alignment(0.5, 0.5, 0, 0);

    p_align->add(*m_dialSwitchLevel);
	p_background->add(*p_align);
    add(*p_background);

	Gtk::manage(p_background);
}

void VCSwitchAudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_switchlevel)
		m_dialSwitchLevel->set_value(*static_cast<const float*> (buffer));
}

static int _ = VCSwitchAudioGUI::register_class("http://github.com/blablack/ams-lv2/vcswitch_audio/gui");
