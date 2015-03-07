#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "haas.hpp"
#include "haas_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "haas_gui.hpp"

HaasGUI::HaasGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	HBox *p_mainWidget = manage (new HBox(true));

	p_mainWidget->pack_start(*(m_dialDelay = CreateDial("Delay (ms)", p_delay, NORMAL, 1)));
	p_mainWidget->pack_start(*(m_dialMix = CreateDial("Dry/Wet (%)", p_dry_wet, NORMAL, 1)));

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_background);
}

void HaasGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch (port)
	{
		case p_delay:
			m_dialDelay->set_value(*static_cast<const float*> (buffer));
			break;
		case p_dry_wet:
			m_dialMix->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

LabeledDial* HaasGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &HaasGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

static int _ = HaasGUI::register_class("http://github.com/blablack/ams-lv2/haas/gui");
