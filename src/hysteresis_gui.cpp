#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "hysteresis.hpp"
#include "hysteresis_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "hysteresis_gui.hpp"

HysteresisGUI::HysteresisGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	p_mainWidget->pack_start(*(m_dialCenter		= CreateDial("Center",		p_center,		NORMAL, 0.01)));
	p_mainWidget->pack_start(*(m_dialOverlap	= CreateDial("Overlap",		p_overlap,		NORMAL, 0.01)));

	p_mainWidget->pack_start(*(m_dialLowSlope	= CreateDial("Low Slope",	p_lowSlope,		NORMAL, 0.01)));
	//p_mainWidget->pack_start(*(m_dialLowOffset	= CreateDial("Low Offset",	p_lowOffset,	NORMAL, 0.01)));

	p_mainWidget->pack_start(*(m_dialHighSlope	= CreateDial("High Slope",	p_highSlope,	NORMAL, 0.01)));
	//p_mainWidget->pack_start(*(m_dialHighOffset	= CreateDial("High Offset", p_highOffset,	NORMAL, 0.01)));

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void HysteresisGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch( port )
	{
		case p_center:
			m_dialCenter->set_value(*static_cast<const float*> (buffer));
			break;
		case p_overlap:
			m_dialOverlap->set_value(*static_cast<const float*> (buffer));
			break;
		case p_lowSlope:
			m_dialLowSlope->set_value(*static_cast<const float*> (buffer));
			break;
			/*
		case p_lowOffset:
			m_dialLowOffset->set_value(*static_cast<const float*> (buffer));
			break;
			*/
		case p_highSlope:
			m_dialHighSlope->set_value(*static_cast<const float*> (buffer));
			break;
			/*
		case p_highOffset:
			m_dialHighOffset->set_value(*static_cast<const float*> (buffer));
			break;
			*/
	}
}

LabeledDial* HysteresisGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &HysteresisGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

static int _ = HysteresisGUI::register_class("http://github.com/blablack/ams-lv2/hysteresis/gui");
