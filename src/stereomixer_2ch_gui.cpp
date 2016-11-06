#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "stereomixer_2ch.hpp"
#include "stereomixer_2ch_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "stereomixer_2ch_gui.hpp"

StereoMixer2ChGUI::StereoMixer2ChGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);


	VBox *p_mainWidget = manage(new VBox(false));


	m_dialMasterVolume = CreateDial("Master Volume", p_masterVolume, 0, 10, NORMAL, 0.01);
	p_mainWidget->pack_start(*m_dialMasterVolume);


	MyBox *p_inBox1 = manage(new MyBox("In 1", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute1 = CreateCheck("Mute", p_mute1);
	p_inBox1->pack_start(*m_checkMute1);

	m_checkSolo1 = CreateCheck("Solo", p_solo1);
	p_inBox1->pack_start(*m_checkSolo1);

	m_dialVolume1 = CreateDial("Volume", p_volume1, 0, 2, NORMAL, 0.01);
	p_inBox1->pack_start(*m_dialVolume1);

	m_dialPan1 = CreateDial("Pan", p_pan1, -1, 1, NORMAL, 0.01);
	p_inBox1->pack_start(*m_dialPan1);

	p_mainWidget->pack_start(*p_inBox1);


	MyBox *p_inBox2 = manage(new MyBox("In 2", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute2 = CreateCheck("Mute", p_mute2);
	p_inBox2->pack_start(*m_checkMute2);

	m_checkSolo2 = CreateCheck("Solo", p_solo2);
	p_inBox2->pack_start(*m_checkSolo2);

	m_dialVolume2 = CreateDial("Volume", p_volume2, 0, 2, NORMAL, 0.01);
	p_inBox2->pack_start(*m_dialVolume2);

	m_dialPan2 = CreateDial("Pan", p_pan2, -1, 1, NORMAL, 0.01);
	p_inBox2->pack_start(*m_dialPan2);

	p_mainWidget->pack_start(*p_inBox2);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

LabeledDial* StereoMixer2ChGUI::CreateDial(const std::string TextLabel, double Value, double Min, double Max, DialType Type, double Step)
{
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, Min, Max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &StereoMixer2ChGUI::write_control), Value), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

CheckButton* StereoMixer2ChGUI::CreateCheck(const std::string TextLabel, int PortNum)
{
	CheckButton* m_tempCheck = manage (new CheckButton(TextLabel, PortNum));
	m_tempCheck->signal_toggled().connect(compose(bind<0>(mem_fun(*this, &StereoMixer2ChGUI::write_control), PortNum), mem_fun(*m_tempCheck, &CheckButton::get_active)));

	return m_tempCheck;
}

void StereoMixer2ChGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_value;

	switch(port)
	{
		case p_masterVolume:
			m_dialMasterVolume->set_value(*static_cast<const float*> (buffer));
			break;

		case p_mute1:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute1->set_active(p_value == 1);
			break;
		case p_solo1:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo1->set_active(p_value == 1);
			break;
		case p_volume1:
			m_dialVolume1->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan1:
			m_dialPan1->set_value(*static_cast<const float*> (buffer));
			break;

		case p_mute2:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute2->set_active(p_value == 1);
			break;
		case p_solo2:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo2->set_active(p_value == 1);
			break;
		case p_volume2:
			m_dialVolume2->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan2:
			m_dialPan2->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = StereoMixer2ChGUI::register_class("http://github.com/blablack/ams-lv2/stereomixer_2ch/gui");
