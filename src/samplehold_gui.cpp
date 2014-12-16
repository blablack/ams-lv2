#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "samplehold.hpp"
#include "samplehold_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "samplehold_gui.hpp"

SampleHoldGUI::SampleHoldGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	m_dialTriggerLevel = new LabeledDial("Trigger Level", 0, 10, LOG, 0.0001);
	m_dialTriggerLevel->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &SampleHoldGUI::write_control), p_triggerLevel), mem_fun(*m_dialTriggerLevel,  &LabeledDial::get_value)));

    Alignment* p_align = new Alignment(0.5, 0.5, 0, 0);

    p_align->add(*m_dialTriggerLevel);
	p_background->add(*p_align);
	add(*p_background);

	Gtk::manage(p_background);
}

void SampleHoldGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_triggerLevel)
		m_dialTriggerLevel->set_value(*static_cast<const float*> (buffer));
}

static int _ = SampleHoldGUI::register_class("http://github.com/blablack/ams-lv2/samplehold/gui");
