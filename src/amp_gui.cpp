#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "amp.hpp"
#include "amp_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "amp_gui.hpp"

AmpGUI::AmpGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	m_dialGain = new LabeledDial("Gain", -10, 10, NORMAL, 0.05);
	m_dialGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AmpGUI::write_control), p_gain), mem_fun(*m_dialGain,  &LabeledDial::get_value)));

	Alignment* p_align = new Alignment(0.5, 0.5, 0, 0);

	p_align->add(*m_dialGain);
	p_background->add(*p_align);
	add(*p_background);

	Gtk::manage(p_background);
}

void AmpGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_gain)
		m_dialGain->set_value(*static_cast<const float*> (buffer));
}

static int _ = AmpGUI::register_class("http://github.com/blablack/ams-lv2/amp/gui");
