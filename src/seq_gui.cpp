#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "seq.hpp"

#if STEP_COUNT == 8
#include "seq_8_ttl.hpp"
#elif STEP_COUNT == 12
#include "seq_12_ttl.hpp"
#elif STEP_COUNT == 16
#include "seq_16_ttl.hpp"
#elif STEP_COUNT == 24
#include "seq_24_ttl.hpp"
#elif STEP_COUNT == 32
#include "seq_32_ttl.hpp"
#endif

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "seq_gui.hpp"

SeqGUI::SeqGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	MyBox *p_main_box = manage (new MyBox("Main", Gtk::Orientation::ORIENTATION_VERTICAL));

	p_main_box->pack_start(*(m_pitchOffset = CreateDial("Pitch Offset", p_pitchOffset, NORMAL, 1)));
	p_main_box->pack_start(*(m_bpm = CreateDial("BPM", p_bpm, NORMAL, 1)));

	MyBox *p_gateTimeBox = manage (new MyBox("Gate Time", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	m_comboGateTime = manage (new ComboBoxText());
	m_comboGateTime->append_text("1");
	m_comboGateTime->append_text("3/4");
	m_comboGateTime->append_text("1/2");
	m_comboGateTime->append_text("1/4");
	m_comboGateTime->signal_changed().connect(mem_fun(*this, &SeqGUI::get_waveform));
	p_gateTimeBox->pack_start(*m_comboGateTime);
	p_main_box->pack_start(*p_gateTimeBox);

	p_mainWidget->pack_start(*p_main_box);


	MyBox *p_pitch_box = manage (new MyBox("Pitch", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	for( int i = 0; i < MODULE_STEP_COUNT; i++ )
	{
		std::string p_label = "";
		if((i)%4 == 0)
			p_label = std::to_string(i+1);
		p_pitch_box->pack_start(*(m_pitches[i] = CreateDial(p_label, index_pitches[i], NORMAL, 1)));
	}
	p_mainWidget->pack_start(*p_pitch_box);


	MyBox *p_gate_box = manage (new MyBox("Gate", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	for( int i = 0; i < MODULE_STEP_COUNT; i++ )
	{
		std::string p_label = "";
		if((i)%4 == 0)
			p_label = std::to_string(i+1);
		p_gate_box->pack_start(*(m_gates[i] = CreateCheck(p_label, index_pitches[i])));
	}
	p_mainWidget->pack_start(*p_gate_box);


	MyBox *p_velocity_box = manage (new MyBox("Velocity", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	for( int i = 0; i < MODULE_STEP_COUNT; i++ )
	{
		std::string p_label = "";
		if((i)%4 == 0)
			p_label = std::to_string(i+1);
		p_velocity_box->pack_start(*(m_velocities[i] = CreateDial(p_label, index_velocities[i], NORMAL, 1)));
	}
	p_mainWidget->pack_start(*p_velocity_box);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void SeqGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_gateTimeValue;
	switch(port)
	{
		case p_gateTime:
			p_gateTimeValue = (int) (*static_cast<const float*> (buffer));
			if (p_gateTimeValue >= 0 && p_gateTimeValue <= 3)
				m_comboGateTime->set_active((int) p_gateTimeValue);
			break;
		case p_bpm:
			m_bpm->set_value(*static_cast<const float*> (buffer));
			break;
		case p_pitchOffset:
			m_pitchOffset->set_value(*static_cast<const float*> (buffer));
			break;
	}
	for( int i = 0; i < MODULE_STEP_COUNT; i++ )
	{
		if( port == index_pitches[i] )
		{
			m_pitches[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == index_gates[i] )
		{
			int p_value = (int) (*static_cast<const float*> (buffer));
			m_gates[i]->set_active(p_value == 1);
		}
		else if( port == index_velocities[i] )
		{
			m_velocities[i]->set_value(*static_cast<const float*> (buffer));
		}
	}
}

LabeledDial* SeqGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &SeqGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

CheckButton* SeqGUI::CreateCheck(const std::string TextLabel, int PortNum)
{
	CheckButton* m_tempCheck = manage (new CheckButton(TextLabel, PortNum));
	m_tempCheck->signal_toggled().connect(compose(bind<0>(mem_fun(*this, &SeqGUI::write_control), PortNum), mem_fun(*m_tempCheck, &CheckButton::get_active)));

	return m_tempCheck;
}

void SeqGUI::get_waveform()
{
	this->write_control(p_gateTime, m_comboGateTime->get_active_row_number());
}


#if STEP_COUNT == 8
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_8/gui");
#elif STEP_COUNT == 12
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_12/gui");
#elif STEP_COUNT == 16
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_16/gui");
#elif STEP_COUNT == 24
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_24/gui");
#elif STEP_COUNT == 32
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_32/gui");
#endif



