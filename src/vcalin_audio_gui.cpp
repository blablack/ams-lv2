#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcalin_audio_gui.hpp"
#include "vcalin_audio.hpp"
#include "dial.hpp"

VCALinAudioGUI::VCALinAudioGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);



	VBox *p_mainWidget = manage(new VBox(false, 5));



	Frame *p_gainFrame = manage(new Frame("Gain"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_gainBox = manage(new HBox(true));

	slot<void> p_slotGain1 = compose(bind<0>(mem_fun(*this, &VCALinAudioGUI::write_control), p_gain1), mem_fun(*this,  &VCALinAudioGUI::get_gain1));
	m_dialGain1 = new LabeledDial("Gain Offset", p_gain1, 0, 1, NORMAL, 0.01, 2);
	m_dialGain1->signal_value_changed().connect(p_slotGain1);
	p_gainBox->pack_start(*m_dialGain1);

	slot<void> p_slotGain2 = compose(bind<0>(mem_fun(*this, &VCALinAudioGUI::write_control), p_gain2), mem_fun(*this,  &VCALinAudioGUI::get_gain2));
	m_dialGain2 = new LabeledDial("2nd Gain Boost", p_gain2, 0, 1, NORMAL, 0.01, 2);
	m_dialGain2->signal_value_changed().connect(p_slotGain2);
	p_gainBox->pack_start(*m_dialGain2);

	p_gainFrame->add(*p_gainBox);
	p_mainWidget->pack_start(*p_gainFrame);



	Frame *p_inFrame = manage(new Frame("In"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_volumeBox = manage(new HBox(true));

	slot<void> p_slotIn1 = compose(bind<0>(mem_fun(*this, &VCALinAudioGUI::write_control), p_in1), mem_fun(*this,  &VCALinAudioGUI::get_in1));
	m_dialIn1 = new LabeledDial("In 1", p_in1, 0, 2, NORMAL, 0.01, 2);
	m_dialIn1->signal_value_changed().connect(p_slotIn1);
	p_volumeBox->pack_start(*m_dialIn1);

	slot<void> p_slotIn2 = compose(bind<0>(mem_fun(*this, &VCALinAudioGUI::write_control), p_in2), mem_fun(*this,  &VCALinAudioGUI::get_in2));
	m_dialIn2 = new LabeledDial("In 2", p_in2, 0, 2, NORMAL, 0.01, 2);
	m_dialIn2->signal_value_changed().connect(p_slotIn2);
	p_volumeBox->pack_start(*m_dialIn2);

	p_inFrame->add(*p_volumeBox);
	p_mainWidget->pack_start(*p_inFrame);



	slot<void> p_slotOutputLevel = compose(bind<0>(mem_fun(*this, &VCALinAudioGUI::write_control), p_outputLevel), mem_fun(*this,  &VCALinAudioGUI::get_outputLevel));
	m_dialOutputLevel = new LabeledDial("Output Level", p_outputLevel, 0, 2, NORMAL, 0.01, 2);
	m_dialOutputLevel->signal_value_changed().connect(p_slotOutputLevel);
	p_mainWidget->pack_start(*m_dialOutputLevel);



	p_mainWidget->set_size_request(150, 300);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float VCALinAudioGUI::get_gain1()		{ return m_dialGain1->get_value(); }
float VCALinAudioGUI::get_gain2()		{ return m_dialGain2->get_value(); }
float VCALinAudioGUI::get_in1()			{ return m_dialIn1->get_value(); }
float VCALinAudioGUI::get_in2()			{ return m_dialIn2->get_value(); }
float VCALinAudioGUI::get_outputLevel()	{ return m_dialOutputLevel->get_value(); }


void VCALinAudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_gain1)
	{
		m_dialGain1->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_gain2)
	{
		m_dialGain2->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_in1)
	{
		m_dialIn1->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_in2)
	{
		m_dialIn2->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_outputLevel)
	{
		m_dialOutputLevel->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = VCALinAudioGUI::register_class("http://github.com/blablack/ams-lv2/vcalin_audio/gui");
