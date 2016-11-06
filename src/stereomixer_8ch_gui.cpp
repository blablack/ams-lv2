#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "stereomixer_8ch.hpp"
#include "stereomixer_8ch_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "stereomixer_8ch_gui.hpp"

StereoMixer8ChGUI::StereoMixer8ChGUI(const std::string& URI)
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


	MyBox *p_inBox3 = manage(new MyBox("In 3", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute3 = CreateCheck("Mute", p_mute3);
	p_inBox3->pack_start(*m_checkMute3);

	m_checkSolo3 = CreateCheck("Solo", p_solo3);
	p_inBox3->pack_start(*m_checkSolo3);

	m_dialVolume3 = CreateDial("Volume", p_volume3, 0, 2, NORMAL, 0.01);
	p_inBox3->pack_start(*m_dialVolume3);

	m_dialPan3 = CreateDial("Pan", p_pan3, -1, 1, NORMAL, 0.01);
	p_inBox3->pack_start(*m_dialPan3);

	p_mainWidget->pack_start(*p_inBox3);


	MyBox *p_inBox4 = manage(new MyBox("In 4", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute4 = CreateCheck("Mute", p_mute4);
	p_inBox4->pack_start(*m_checkMute4);

	m_checkSolo4 = CreateCheck("Solo", p_solo4);
	p_inBox4->pack_start(*m_checkSolo4);

	m_dialVolume4 = CreateDial("Volume", p_volume4, 0, 2, NORMAL, 0.01);
	p_inBox4->pack_start(*m_dialVolume4);

	m_dialPan4 = CreateDial("Pan", p_pan4, -1, 1, NORMAL, 0.01);
	p_inBox4->pack_start(*m_dialPan4);

	p_mainWidget->pack_start(*p_inBox4);


	MyBox *p_inBox5 = manage(new MyBox("In 5", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute5 = CreateCheck("Mute", p_mute5);
	p_inBox5->pack_start(*m_checkMute5);

	m_checkSolo5 = CreateCheck("Solo", p_solo5);
	p_inBox5->pack_start(*m_checkSolo5);

	m_dialVolume5 = CreateDial("Volume", p_volume5, 0, 2, NORMAL, 0.01);
	p_inBox5->pack_start(*m_dialVolume5);

	m_dialPan5 = CreateDial("Pan", p_pan5, -1, 1, NORMAL, 0.01);
	p_inBox5->pack_start(*m_dialPan5);

	p_mainWidget->pack_start(*p_inBox5);


	MyBox *p_inBox6 = manage(new MyBox("In 6", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute6 = CreateCheck("Mute", p_mute6);
	p_inBox6->pack_start(*m_checkMute6);

	m_checkSolo6 = CreateCheck("Solo", p_solo6);
	p_inBox6->pack_start(*m_checkSolo6);

	m_dialVolume6 = CreateDial("Volume", p_volume6, 0, 2, NORMAL, 0.01);
	p_inBox6->pack_start(*m_dialVolume6);

	m_dialPan6 = CreateDial("Pan", p_pan6, -1, 1, NORMAL, 0.01);
	p_inBox6->pack_start(*m_dialPan6);

	p_mainWidget->pack_start(*p_inBox6);


	MyBox *p_inBox7 = manage(new MyBox("In 7", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute7 = CreateCheck("Mute", p_mute7);
	p_inBox7->pack_start(*m_checkMute7);

	m_checkSolo7 = CreateCheck("Solo", p_solo7);
	p_inBox7->pack_start(*m_checkSolo7);

	m_dialVolume7 = CreateDial("Volume", p_volume7, 0, 2, NORMAL, 0.01);
	p_inBox7->pack_start(*m_dialVolume7);

	m_dialPan7 = CreateDial("Pan", p_pan7, -1, 1, NORMAL, 0.01);
	p_inBox7->pack_start(*m_dialPan7);

	p_mainWidget->pack_start(*p_inBox7);


	MyBox *p_inBox8 = manage(new MyBox("In 4", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_checkMute8 = CreateCheck("Mute", p_mute8);
	p_inBox8->pack_start(*m_checkMute8);

	m_checkSolo8 = CreateCheck("Solo", p_solo8);
	p_inBox8->pack_start(*m_checkSolo8);

	m_dialVolume8 = CreateDial("Volume", p_volume8, 0, 2, NORMAL, 0.01);
	p_inBox8->pack_start(*m_dialVolume8);

	m_dialPan8 = CreateDial("Pan", p_pan8, -1, 1, NORMAL, 0.01);
	p_inBox8->pack_start(*m_dialPan8);

	p_mainWidget->pack_start(*p_inBox8);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

LabeledDial* StereoMixer8ChGUI::CreateDial(const std::string TextLabel, double Value, double Min, double Max, DialType Type, double Step)
{
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, Min, Max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &StereoMixer8ChGUI::write_control), Value), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

CheckButton* StereoMixer8ChGUI::CreateCheck(const std::string TextLabel, int PortNum)
{
	CheckButton* m_tempCheck = manage (new CheckButton(TextLabel, PortNum));
	m_tempCheck->signal_toggled().connect(compose(bind<0>(mem_fun(*this, &StereoMixer8ChGUI::write_control), PortNum), mem_fun(*m_tempCheck, &CheckButton::get_active)));

	return m_tempCheck;
}


void StereoMixer8ChGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
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


		case p_mute3:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute3->set_active(p_value == 1);
			break;
		case p_solo3:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo3->set_active(p_value == 1);
			break;
		case p_volume3:
			m_dialVolume3->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan3:
			m_dialPan3->set_value(*static_cast<const float*> (buffer));
			break;


		case p_mute4:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute4->set_active(p_value == 1);
			break;
		case p_solo4:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo4->set_active(p_value == 1);
			break;
		case p_volume4:
			m_dialVolume4->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan4:
			m_dialPan4->set_value(*static_cast<const float*> (buffer));
			break;

		case p_mute5:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute5->set_active(p_value == 1);
			break;
		case p_solo5:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo5->set_active(p_value == 1);
			break;
		case p_volume5:
			m_dialVolume5->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan5:
			m_dialPan5->set_value(*static_cast<const float*> (buffer));
			break;

		case p_mute6:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute6->set_active(p_value == 1);
			break;
		case p_solo6:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo6->set_active(p_value == 1);
			break;
		case p_volume6:
			m_dialVolume6->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan6:
			m_dialPan6->set_value(*static_cast<const float*> (buffer));
			break;


		case p_mute7:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute7->set_active(p_value == 1);
			break;
		case p_solo7:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo7->set_active(p_value == 1);
			break;
		case p_volume7:
			m_dialVolume7->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan7:
			m_dialPan7->set_value(*static_cast<const float*> (buffer));
			break;


		case p_mute8:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkMute8->set_active(p_value == 1);
			break;
		case p_solo8:
			p_value = (int) (*static_cast<const float*> (buffer));
			m_checkSolo8->set_active(p_value == 1);
			break;
		case p_volume8:
			m_dialVolume8->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pan8:
			m_dialPan8->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = StereoMixer8ChGUI::register_class("http://github.com/blablack/ams-lv2/stereomixer_8ch/gui");
