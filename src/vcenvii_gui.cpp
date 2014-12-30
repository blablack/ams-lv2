#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "vcenvii.hpp"
#include "vcenvii_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vcenvii_gui.hpp"

VCEnvIIGUI::VCEnvIIGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);


	VBox *p_mainWidget = manage(new VBox(false));


	MyBox *p_offsetFrame = manage (new MyBox("Offset", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	p_offsetFrame->pack_start(*(m_dialAttackOffset	= CreateDial("Attack",	p_attackOffset,		NORMAL, 0.01)));
	p_offsetFrame->pack_start(*(m_dialDecayOffset	= CreateDial("Decay",	p_decayOffset,		NORMAL, 0.01)));
	p_offsetFrame->pack_start(*(m_dialSustainOffset = CreateDial("Sustain", p_sustainOffset,	NORMAL, 0.01)));
	p_offsetFrame->pack_start(*(m_dialReleaseOffset = CreateDial("Release", p_releaseOffset,	NORMAL, 0.01)));
	p_mainWidget->pack_start(*p_offsetFrame);


	MyBox *p_gainFrame = manage(new MyBox("Gain", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	p_gainFrame->pack_start(*(m_dialAttackGain	=	 CreateDial("Attack",	p_attackGain,		NORMAL, 0.01)));
	p_gainFrame->pack_start(*(m_dialDecayGain		= CreateDial("Decay",	p_decayGain,		NORMAL, 0.01)));
	p_gainFrame->pack_start(*(m_dialSustainGain		= CreateDial("Sustain", p_sustainGain,		NORMAL, 0.01)));
	p_gainFrame->pack_start(*(m_dialReleaseGain		= CreateDial("Release", p_releaseGain,		NORMAL, 0.01)));
	p_mainWidget->pack_start(*p_gainFrame);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

LabeledDial* VCEnvIIGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCEnvIIGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}


void VCEnvIIGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	int p_value;
	switch(port)
	{
		case p_attackOffset:
			m_dialAttackOffset->set_value(*static_cast<const float*> (buffer));
			break;
		case p_decayOffset:
			m_dialDecayOffset->set_value(*static_cast<const float*> (buffer));
			break;
		case p_sustainOffset:
			m_dialSustainOffset->set_value(*static_cast<const float*> (buffer));
			break;
		case p_releaseOffset:
			m_dialReleaseOffset->set_value(*static_cast<const float*> (buffer));
			break;
		case p_attackGain:
			m_dialAttackGain->set_value(*static_cast<const float*> (buffer));
			break;
		case p_decayGain:
			m_dialDecayGain->set_value(*static_cast<const float*> (buffer));
			break;
		case p_sustainGain:
			m_dialSustainGain->set_value(*static_cast<const float*> (buffer));
			break;
		case p_releaseGain:
			m_dialReleaseGain->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = VCEnvIIGUI::register_class("http://github.com/blablack/ams-lv2/vcenvii/gui");
