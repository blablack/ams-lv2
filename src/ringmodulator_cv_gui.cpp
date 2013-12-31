#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "ringmodulator_cv_gui.hpp"
#include "ringmodulator_cv.hpp"
#include "dial.hpp"

RindModulatorCVGUI::RindModulatorCVGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotGain = compose(bind<0>(mem_fun(*this, &RindModulatorCVGUI::write_control), p_gain), mem_fun(*this,  &RindModulatorCVGUI::get_gain));
	m_dialGain = new LabeledDial("Gain", p_gain, -10, 10, NORMAL, 0.01, 2);
	m_dialGain->signal_value_changed().connect(p_slotGain);
	p_background->add(*m_dialGain);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float RindModulatorCVGUI::get_gain() { return m_dialGain->get_value(); }

void RindModulatorCVGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_gain)
	{
		m_dialGain->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = RindModulatorCVGUI::register_class("http://github.com/blablack/ams-lv2/ringmodulator_cv/gui");
