#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "bitgrinder.hpp"
#include "bitgrinder_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "bitgrinder_gui.hpp"

BitGrinderGUI::BitGrinderGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false));

	p_mainWidget->pack_start(*(m_dialFractionalDataRate	= CreateDial("Fractional data rate",	p_fractionaldatarate,	NORMAL, 0.001)));
	p_mainWidget->pack_start(*(m_dialRateVCModulation	= CreateDial("Rate VC modulation",		p_ratevcmodulation,		NORMAL, 0.001)));

	p_mainWidget->pack_start(*(m_dialBitsPerVolt		= CreateDial("Bits per Volt",			p_bitspervolt,			NORMAL, 0.01)));
	p_mainWidget->pack_start(*(m_dialBitsVCModulation	= CreateDial("Bits VC modulation",		p_bitsvcmodulation,		NORMAL, 0.001)));

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void BitGrinderGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch( port )
	{
		case p_fractionaldatarate:
			m_dialFractionalDataRate->set_value(*static_cast<const float*> (buffer));
			break;
		case p_ratevcmodulation:
			m_dialRateVCModulation->set_value(*static_cast<const float*> (buffer));
			break;
		case p_bitspervolt:
			m_dialBitsPerVolt->set_value(*static_cast<const float*> (buffer));
			break;
		case p_bitsvcmodulation:
			m_dialBitsVCModulation->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

LabeledDial* BitGrinderGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &BitGrinderGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

static int _ = BitGrinderGUI::register_class("http://github.com/blablack/ams-lv2/bitgrinder/gui");
