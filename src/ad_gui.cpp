#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "ad.hpp"

#if OUT_COUNT == 2
#include "ad_2_ttl.hpp"
#elif OUT_COUNT == 4
#include "ad_4_ttl.hpp"
#elif OUT_COUNT == 6
#include "ad_6_ttl.hpp"
#endif

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "ad_gui.hpp"

AdGUI::AdGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	HBox *p_mainWidget = manage(new HBox(true));

	MyBox *p_detuneFrame = manage(new MyBox("Detune", Gtk::Orientation::ORIENTATION_VERTICAL));

	m_dialDetuneAmplitude = new LabeledDial("Amplitude", 0, 0.084, LOG, 0.00001);
	m_dialDetuneAmplitude->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneAmplitude), mem_fun(*m_dialDetuneAmplitude,  &LabeledDial::get_value)));
	p_detuneFrame->pack_start(*m_dialDetuneAmplitude);

	m_dialDetuneModulation = new LabeledDial("Modulation", 0.01, 1, LOG, 0.0001);
	m_dialDetuneModulation->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneModulation), mem_fun(*m_dialDetuneModulation,  &LabeledDial::get_value)));
	p_detuneFrame->pack_start(*m_dialDetuneModulation);

	m_dialDetuneRate = new LabeledDial("Rate", 0.01, 10, LOG, 0.0001);
	m_dialDetuneRate->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneRate), mem_fun(*m_dialDetuneRate,  &LabeledDial::get_value)));
	p_detuneFrame->pack_start(*m_dialDetuneRate);

	p_mainWidget->pack_start(*p_detuneFrame);


	MyBox *p_driftFrame = manage(new MyBox("Drift", Gtk::Orientation::ORIENTATION_VERTICAL));

	m_dialDriftAmplitude = new LabeledDial("Amplitude", 0, 0.084, LOG, 0.00001);
	m_dialDriftAmplitude->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftAmplitude), mem_fun(*m_dialDriftAmplitude,  &LabeledDial::get_value)));
	p_driftFrame->pack_start(*m_dialDriftAmplitude);

	m_dialDriftModulation = new LabeledDial("Modulation", 0.01, 1, LOG, 0.0001);
	m_dialDriftModulation->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftModulation), mem_fun(*m_dialDriftModulation,  &LabeledDial::get_value)));
	p_driftFrame->pack_start(*m_dialDriftModulation);

	m_dialDriftRate = new LabeledDial("Rate", 0.01, 10, LOG, 0.0001);
	m_dialDriftRate->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftRate), mem_fun(*m_dialDriftRate,  &LabeledDial::get_value)));
	p_driftFrame->pack_start(*m_dialDriftRate);

	p_mainWidget->pack_start(*p_driftFrame);


	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

void AdGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch(port)
	{
		case p_detuneAmplitude:
			m_dialDetuneAmplitude->set_value(*static_cast<const float*> (buffer));
			break;
		case p_detuneModulation:
			m_dialDetuneModulation->set_value(*static_cast<const float*> (buffer));
			break;
		case p_detuneRate:
			m_dialDetuneRate->set_value(*static_cast<const float*> (buffer));
			break;
		case p_driftAmplitude:
			m_dialDriftAmplitude->set_value(*static_cast<const float*> (buffer));
			break;
		case p_driftModulation:
			m_dialDriftModulation->set_value(*static_cast<const float*> (buffer));
			break;
		case p_driftRate:
			m_dialDriftRate->set_value(*static_cast<const float*> (buffer));
			break;
	}
}

#if OUT_COUNT == 2
static int _ = AdGUI::register_class("http://github.com/blablack/ams-lv2/ad_2/gui");
#elif OUT_COUNT == 4
static int _ = AdGUI::register_class("http://github.com/blablack/ams-lv2/ad_4/gui");
#elif OUT_COUNT == 6
static int _ = AdGUI::register_class("http://github.com/blablack/ams-lv2/ad_6/gui");
#endif
