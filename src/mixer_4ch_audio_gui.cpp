#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "mixer_4ch_audio_gui.hpp"
#include "mixer_4ch_audio.hpp"
#include "dial.hpp"

Mixer4ChAudioGUI::Mixer4ChAudioGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);



	VBox *p_mainWidget = manage(new VBox(false, 5));



	slot<void> p_slotGain = compose(bind<0>(mem_fun(*this, &Mixer4ChAudioGUI::write_control), p_gain), mem_fun(*this,  &Mixer4ChAudioGUI::get_gain));
	m_dialGain = new LabeledDial("Gain", p_gain, 0, 2, NORMAL, 0.01, 2);
	m_dialGain->signal_value_changed().connect(p_slotGain);
	p_mainWidget->pack_start(*m_dialGain);



	Frame *p_volumesFrame = manage(new Frame("Volumes"));
	p_volumesFrame->set_shadow_type(Gtk::SHADOW_NONE);
	Table *p_volumesBox = manage(new Table(2, 2, true));

	slot<void> p_slotVolume1 = compose(bind<0>(mem_fun(*this, &Mixer4ChAudioGUI::write_control), p_volume1), mem_fun(*this,  &Mixer4ChAudioGUI::get_volume1));
	m_dialVolume1 = new LabeledDial("Volume 1", p_volume1, 0, 2, NORMAL, 0.01, 2);
	m_dialVolume1->signal_value_changed().connect(p_slotVolume1);
	p_volumesBox->attach(*m_dialVolume1, 0, 1, 0, 1);

	slot<void> p_slotVolume2 = compose(bind<0>(mem_fun(*this, &Mixer4ChAudioGUI::write_control), p_volume2), mem_fun(*this,  &Mixer4ChAudioGUI::get_volume2));
	m_dialVolume2 = new LabeledDial("Volume 2", p_volume2, 0, 2, NORMAL, 0.01, 2);
	m_dialVolume2->signal_value_changed().connect(p_slotVolume2);
	p_volumesBox->attach(*m_dialVolume2, 1, 2, 0, 1);

	slot<void> p_slotVolume3 = compose(bind<0>(mem_fun(*this, &Mixer4ChAudioGUI::write_control), p_volume3), mem_fun(*this,  &Mixer4ChAudioGUI::get_volume3));
	m_dialVolume3 = new LabeledDial("Volume 3", p_volume3, 0, 2, NORMAL, 0.01, 2);
	m_dialVolume3->signal_value_changed().connect(p_slotVolume3);
	p_volumesBox->attach(*m_dialVolume3, 0, 1, 1, 2);

	slot<void> p_slotVolume4 = compose(bind<0>(mem_fun(*this, &Mixer4ChAudioGUI::write_control), p_volume4), mem_fun(*this,  &Mixer4ChAudioGUI::get_volume4));
	m_dialVolume4 = new LabeledDial("Volume 4", p_volume4, 0, 2, NORMAL, 0.01, 2);
	m_dialVolume4->signal_value_changed().connect(p_slotVolume4);
	p_volumesBox->attach(*m_dialVolume4, 1, 2, 1, 2);

	p_volumesFrame->add(*p_volumesBox);
	p_mainWidget->pack_start(*p_volumesFrame);



	p_mainWidget->set_size_request(150, 300);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float Mixer4ChAudioGUI::get_gain(){ return m_dialGain->get_value(); }
float Mixer4ChAudioGUI::get_volume1(){ return m_dialVolume1->get_value(); }
float Mixer4ChAudioGUI::get_volume2(){ return m_dialVolume2->get_value(); }
float Mixer4ChAudioGUI::get_volume3(){ return m_dialVolume3->get_value(); }
float Mixer4ChAudioGUI::get_volume4(){ return m_dialVolume4->get_value(); }


void Mixer4ChAudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_gain)
	{
		m_dialGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_volume1)
	{
		m_dialVolume1->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_volume2)
	{
		m_dialVolume2->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_volume3)
	{
		m_dialVolume3->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_volume4)
	{
		m_dialVolume4->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = Mixer4ChAudioGUI::register_class("http://github.com/blablack/ams-lv2/mixer_4ch_audio/gui");
