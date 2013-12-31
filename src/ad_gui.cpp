#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "ad_gui.hpp"
#include "ad.hpp"
#include "dial.hpp"

AdGUI::AdGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	HBox *p_mainWidget = manage(new HBox(true));

	Frame *p_detuneFrame = manage(new Frame("Detune"));
	VBox *p_detuneBox = manage(new VBox(false));

	slot<void> p_slotDetuneAmplitude = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneAmplitude), mem_fun(*this,  &AdGUI::get_detuneAmplitude));
	m_dialDetuneAmplitude = new LabeledDial("Amplitude", p_detuneAmplitude, 0, 0.084, LOG, 0.00001, 5);
	m_dialDetuneAmplitude->signal_value_changed().connect(p_slotDetuneAmplitude);
	p_detuneBox->pack_start(*m_dialDetuneAmplitude);

	slot<void> p_slotDetuneModulation = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneModulation), mem_fun(*this,  &AdGUI::get_detuneModulation));
	m_dialDetuneModulation = new LabeledDial("Modulation", p_detuneModulation, 0.01, 1, LOG, 0.0001, 4);
	m_dialDetuneModulation->signal_value_changed().connect(p_slotDetuneModulation);
	p_detuneBox->pack_start(*m_dialDetuneModulation);

	slot<void> p_slotDetuneRate = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_detuneRate), mem_fun(*this,  &AdGUI::get_detuneRate));
	m_dialDetuneRate = new LabeledDial("Rate", p_detuneRate, 0.01, 10, LOG, 0.0001, 4);
	m_dialDetuneRate->signal_value_changed().connect(p_slotDetuneRate);
	p_detuneBox->pack_start(*m_dialDetuneRate);

	p_detuneFrame->add(*p_detuneBox);
	p_mainWidget->pack_start(*p_detuneFrame);



	Frame *p_driftFrame = manage(new Frame("Drift"));
	VBox *p_driftBox = manage(new VBox(false));

	slot<void> p_slotDriftAmplitude = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftAmplitude), mem_fun(*this,  &AdGUI::get_driftAmplitude));
	m_dialDriftAmplitude = new LabeledDial("Amplitude", p_driftAmplitude, 0, 0.084, LOG, 0.00001, 5);
	m_dialDriftAmplitude->signal_value_changed().connect(p_slotDriftAmplitude);
	p_driftBox->pack_start(*m_dialDriftAmplitude);

	slot<void> p_slotDriftModulation = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftModulation), mem_fun(*this,  &AdGUI::get_driftModulation));
	m_dialDriftModulation = new LabeledDial("Modulation", p_driftModulation, 0.01, 1, LOG, 0.0001, 4);
	m_dialDriftModulation->signal_value_changed().connect(p_slotDriftModulation);
	p_driftBox->pack_start(*m_dialDriftModulation);

	slot<void> p_slotDriftRate = compose(bind<0>(mem_fun(*this, &AdGUI::write_control), p_driftRate), mem_fun(*this,  &AdGUI::get_driftRate));
	m_dialDriftRate = new LabeledDial("Rate", p_driftRate, 0.01, 10, LOG, 0.0001, 4);
	m_dialDriftRate->signal_value_changed().connect(p_slotDriftRate);
	p_driftBox->pack_start(*m_dialDriftRate);

	p_driftFrame->add(*p_driftBox);
	p_mainWidget->pack_start(*p_driftFrame);

	p_mainWidget->set_size_request(256, 320);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float AdGUI::get_detuneAmplitude(){ return m_dialDetuneAmplitude->get_value(); }
float AdGUI::get_detuneModulation(){ return m_dialDetuneModulation->get_value(); }
float AdGUI::get_detuneRate(){ return m_dialDetuneRate->get_value(); }
float AdGUI::get_driftAmplitude(){ return m_dialDriftAmplitude->get_value(); }
float AdGUI::get_driftModulation(){ return m_dialDriftModulation->get_value(); }
float AdGUI::get_driftRate(){ return m_dialDriftRate->get_value(); }

void AdGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_detuneAmplitude)
	{
		m_dialDetuneAmplitude->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_detuneModulation)
	{
		m_dialDetuneModulation->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_detuneRate)
	{
		m_dialDetuneRate->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_driftAmplitude)
	{
		m_dialDriftAmplitude->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_driftModulation)
	{
		m_dialDriftModulation->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_driftRate)
	{
		m_dialDriftRate->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = AdGUI::register_class("http://github.com/blablack/ams-lv2/ad/gui");
