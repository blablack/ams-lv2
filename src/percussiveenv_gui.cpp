#include <gtkmm-2.4/gtkmm.h>
#include <gdkmm-2.4/gdkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "percussiveenv_gui.hpp"
#include "percussiveenv_gui_scope.hpp"
#include "percussiveenv.hpp"
#include "dial.hpp"

PercussiveEnvGUI::PercussiveEnvGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false, 5));

	m_envScope = new PercussiveEnvGUIScope();
	p_mainWidget->pack_start(*m_envScope);



	Frame *p_adsrFrame = manage (new Frame("AD"));
	p_adsrFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_adsrWidget = manage (new HBox(false));

	slot<void> p_slotAttack = compose(bind<0>(mem_fun(*this, &PercussiveEnvGUI::write_control), p_attack), mem_fun(*this, &PercussiveEnvGUI::get_attack));
	m_scaleAttack = new LabeledDial("Attack", p_slotAttack, p_attack, 0, 1, NORMAL, 0.01, 2);
	p_adsrWidget->pack_start(*m_scaleAttack);

	slot<void> p_slotDecay = compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_decay), mem_fun(*this, &PercussiveEnvGUI::get_decay));
	m_scaleDecay = new LabeledDial("Decay", p_slotDecay, p_decay, 0, 1, NORMAL, 0.01, 2);
	p_adsrWidget->pack_start(*m_scaleDecay);

	p_adsrFrame->add(*p_adsrWidget);
	p_mainWidget->pack_start(*p_adsrFrame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_dhtFrame = manage (new Frame("Delay / Hold / Time Scale"));
	p_dhtFrame->set_shadow_type(Gtk::SHADOW_NONE);
		HBox *p_dhtWidget = manage (new HBox(false));

	slot<void> p_slotDelay = compose(bind<0>(mem_fun(*this, &PercussiveEnvGUI::write_control), p_delay), mem_fun(*this, &PercussiveEnvGUI::get_delay));
	m_scaleDelay = new LabeledDial("Delay", p_slotDelay, p_delay, 0, 1, NORMAL, 0.01, 2);
	p_dhtWidget->pack_start(*m_scaleDelay);

	slot<void> p_slotHold = compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_hold), mem_fun(*this, &PercussiveEnvGUI::get_hold));
	m_scaleHold = new LabeledDial("Hold", p_slotHold, p_hold, 0, 1, NORMAL, 0.01, 2);
	p_dhtWidget->pack_start(*m_scaleHold);

	slot<void> p_slotTimescale = compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_timeScale), mem_fun(*this, &PercussiveEnvGUI::get_timescale));
	m_scaleTimeScale = new LabeledDial("Time Scale", p_slotTimescale, p_timeScale, 0, 10, NORMAL, 0.01, 2);
	p_dhtWidget->pack_start(*m_scaleTimeScale);

	p_dhtFrame->add(*p_dhtWidget);
	p_mainWidget->pack_start(*p_dhtFrame);



	m_envScope->m_attackValue = m_scaleAttack->get_value();
	m_envScope->m_decayValue = m_scaleDecay->get_value();
	m_envScope->m_delayValue = m_scaleDelay->get_value();
	m_envScope->m_holdValue = m_scaleHold->get_value();

	m_envScope->Redraw();



	p_mainWidget->set_size_request(200, 320);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float PercussiveEnvGUI::get_attack() { return m_scaleAttack->get_value(); }
float PercussiveEnvGUI::get_decay() { return m_scaleDecay->get_value(); }
float PercussiveEnvGUI::get_delay() { return m_scaleDelay->get_value(); }
float PercussiveEnvGUI::get_hold() { return m_scaleHold->get_value(); }
float PercussiveEnvGUI::get_timescale() { return m_scaleTimeScale->get_value(); }

void PercussiveEnvGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_attack)
	{
		m_attackValue = *static_cast<const float*> (buffer);
		m_scaleAttack->set_value(m_attackValue);
		m_envScope->m_attackValue = m_attackValue;
		m_envScope->Redraw();
	}
	else if (port == p_decay)
	{
		m_decayValue = *static_cast<const float*> (buffer);
		m_scaleDecay->set_value(m_decayValue);
		m_envScope->m_decayValue = m_decayValue;
		m_envScope->Redraw();
	}
	else if (port == p_delay)
	{
		m_delayValue = *static_cast<const float*> (buffer);
		m_scaleDelay->set_value(m_delayValue);
		m_envScope->m_delayValue = m_delayValue;
		m_envScope->Redraw();
	}
	else if (port == p_hold)
	{
		m_holdValue = *static_cast<const float*> (buffer);
		m_scaleHold->set_value(m_holdValue);
		m_envScope->m_holdValue = m_holdValue;
		m_envScope->Redraw();
	}
	else if (port == p_timeScale)
	{
		m_scaleTimeScale->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = PercussiveEnvGUI::register_class("http://github.com/blablack/ams-lv2/percussiveenv/gui");
