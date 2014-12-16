#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "mixer_2ch.hpp"
#include "mixer_2ch_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "mixer_2ch_gui.hpp"

Mixer2ChGUI::Mixer2ChGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);


	VBox *p_mainWidget = manage(new VBox(false));


	m_dialGain = new LabeledDial("Gain", 0, 2, NORMAL, 0.01);
	m_dialGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer2ChGUI::write_control), p_gain), mem_fun(*m_dialGain,  &LabeledDial::get_value)));
	p_mainWidget->pack_start(*m_dialGain);


	HBox *p_volumesFrame = manage(new HBox(true));

	m_dialVolume1 = new LabeledDial("Volume 1", 0, 2, NORMAL, 0.01);
	m_dialVolume1->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer2ChGUI::write_control), p_volume1), mem_fun(*m_dialVolume1,  &LabeledDial::get_value)));
	p_volumesFrame->pack_start(*m_dialVolume1);

	m_dialVolume2 = new LabeledDial("Volume 2", 0, 2, NORMAL, 0.01);
	m_dialVolume2->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer2ChGUI::write_control), p_volume2), mem_fun(*m_dialVolume2,  &LabeledDial::get_value)));
	p_volumesFrame->pack_start(*m_dialVolume2);

	p_mainWidget->pack_start(*p_volumesFrame);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void Mixer2ChGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch(port)
	{
		case p_gain:
			m_dialGain->set_value(*static_cast<const float*> (buffer));
			break;
		case p_volume1:
			m_dialVolume1->set_value(*static_cast<const float*> (buffer));
			break;
		case p_volume2:
			m_dialVolume2->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

static int _ = Mixer2ChGUI::register_class("http://github.com/blablack/ams-lv2/mixer_2ch/gui");
