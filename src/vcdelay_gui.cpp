#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "vcdelay.hpp"
#include "vcdelay_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vcdelay_gui.hpp"

VCDelayGUI::VCDelayGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage(new VBox(false));

	m_dialDelay = new LabeledDial("Delay", 0, 10, LOG, 0.001);
	m_dialDelay->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCDelayGUI::write_control), p_delay), mem_fun(*m_dialDelay,  &LabeledDial::get_value)));
	p_mainWidget->pack_start(*m_dialDelay);

	m_dialVMod = new LabeledDial("V Mod", 0, 1, NORMAL, 0.001);
	m_dialVMod->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCDelayGUI::write_control), p_vmod), mem_fun(*m_dialDelay,  &LabeledDial::get_value)));
	p_mainWidget->pack_start(*m_dialVMod);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_background);
}

void VCDelayGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch(port)
	{
		case p_delay:
			m_dialDelay->set_value(*static_cast<const float*> (buffer));
			break;
		case p_vmod:
			m_dialVMod->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = VCDelayGUI::register_class("http://github.com/blablack/ams-lv2/vcdelay/gui");
