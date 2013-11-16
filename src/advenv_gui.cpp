#include <gtkmm-2.4/gtkmm.h>
#include <gdkmm-2.4/gdkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "advenv_gui.hpp"
#include "advenv_gui_scope.hpp"
#include "advenv.hpp"
#include "dial.hpp"

AdvEnvGUI::AdvEnvGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainWidget = manage (new VBox(false, 5));

	m_envScope = new AdvEnvGUIScope();
	p_mainWidget->pack_start(*m_envScope);




	Frame *p_scaleFrame = manage (new Frame("Time Scale / Sustain / Delay"));
	p_scaleFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_scaleWidget = manage (new HBox(false));

	slot<void> p_slotTimeScale = compose(bind<0>(mem_fun(*this, &AdvEnvGUI::write_control), p_timeScale), mem_fun(*this, &AdvEnvGUI::get_timeScale));
	m_scaleTimeScale = new LabeledDial("Time Scale", p_slotTimeScale, p_timeScale, 0.1, 10, NORMAL, 0.01, 2);
	p_scaleWidget->pack_start(*m_scaleTimeScale);

	slot<void> p_slotSustain = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_sustain), mem_fun(*this, &AdvEnvGUI::get_sustain));
	m_scaleSustain = new LabeledDial("Sustain", p_slotSustain, p_sustain, 0, 1, NORMAL, 0.01, 2);
	p_scaleWidget->pack_start(*m_scaleSustain);

	slot<void> p_slotDelay = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_delay), mem_fun(*this, &AdvEnvGUI::get_delay));
	m_scaleDelay = new LabeledDial("Delay", p_slotDelay, p_delay, 0, 1, NORMAL, 0.01, 2);
	p_scaleWidget->pack_start(*m_scaleDelay);

	p_scaleFrame->add(*p_scaleWidget);
	p_mainWidget->pack_start(*p_scaleFrame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_attackTimeFrame = manage (new Frame("Attack Time"));
	p_attackTimeFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_attackTimeWidget = manage (new HBox(false));

	slot<void> p_slotAttackTime1 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime1), mem_fun(*this, &AdvEnvGUI::get_attackTime1));
	m_scaleAttackTime1 = new LabeledDial("Attack Time 1", p_slotAttackTime1, p_attackTime1, 0, 1, NORMAL, 0.01, 2);
	p_attackTimeWidget->pack_start(*m_scaleAttackTime1);

	slot<void> p_slotAttackTime2 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime2), mem_fun(*this, &AdvEnvGUI::get_attackTime2));
	m_scaleAttackTime2 = new LabeledDial("Attack Time 2", p_slotAttackTime2, p_attackTime2, 0, 1, NORMAL, 0.01, 2);
	p_attackTimeWidget->pack_start(*m_scaleAttackTime2);

	slot<void> p_slotAttackTime3 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime3), mem_fun(*this, &AdvEnvGUI::get_attackTime3));
	m_scaleAttackTime3 = new LabeledDial("Attack Time 3", p_slotAttackTime3, p_attackTime3, 0, 1, NORMAL, 0.01, 2);
	p_attackTimeWidget->pack_start(*m_scaleAttackTime3);

	slot<void> p_slotAttackTime4 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime4), mem_fun(*this, &AdvEnvGUI::get_attackTime4));
	m_scaleAttackTime4 = new LabeledDial("Attack Time 4", p_slotAttackTime4, p_attackTime4, 0, 1, NORMAL, 0.01, 2);
	p_attackTimeWidget->pack_start(*m_scaleAttackTime4);

	p_attackTimeFrame->add(*p_attackTimeWidget);
	p_mainWidget->pack_start(*p_attackTimeFrame);



	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_attackLevelFrame = manage (new Frame("Attack Level"));
	p_attackLevelFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_attackLevelWidget = manage (new HBox(false));

	slot<void> p_slotAttackLevel1 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel1), mem_fun(*this, &AdvEnvGUI::get_attackLevel1));
	m_scaleAttackLevel1 = new LabeledDial("Attack Level 1", p_slotAttackLevel1, p_attackLevel1, 0, 1, NORMAL, 0.01, 2);
	p_attackLevelWidget->pack_start(*m_scaleAttackLevel1);

	slot<void> p_slotAttackLevel2 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel2), mem_fun(*this, &AdvEnvGUI::get_attackLevel2));
	m_scaleAttackLevel2 = new LabeledDial("Attack Level 2", p_slotAttackLevel2, p_attackLevel2, 0, 1, NORMAL, 0.01, 2);
	p_attackLevelWidget->pack_start(*m_scaleAttackLevel2);

	slot<void> p_slotAttackLevel3 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel3), mem_fun(*this, &AdvEnvGUI::get_attackLevel3));
	m_scaleAttackLevel3 = new LabeledDial("Attack Level 3", p_slotAttackLevel3, p_attackLevel3, 0, 1, NORMAL, 0.01, 2);
	p_attackLevelWidget->pack_start(*m_scaleAttackLevel3);

	p_attackLevelFrame->add(*p_attackLevelWidget);
	p_mainWidget->pack_start(*p_attackLevelFrame);


	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_releaseTimeFrame = manage (new Frame("Release Time"));
	p_releaseTimeFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_releaseTimeWidget = manage (new HBox(false));

	slot<void> p_slotReleaseTime1 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime1), mem_fun(*this, &AdvEnvGUI::get_releaseTime1));
	m_scaleReleaseTime1 = new LabeledDial("Release Time 1", p_slotReleaseTime1, p_releaseTime1, 0, 1, NORMAL, 0.01, 2);
	p_releaseTimeWidget->pack_start(*m_scaleReleaseTime1);

	slot<void> p_slotReleaseTime2 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime2), mem_fun(*this, &AdvEnvGUI::get_releaseTime2));
	m_scaleReleaseTime2 = new LabeledDial("Release Time 2", p_slotReleaseTime2, p_releaseTime2, 0, 1, NORMAL, 0.01, 2);
	p_releaseTimeWidget->pack_start(*m_scaleReleaseTime2);

	slot<void> p_slotReleaseTime3 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime3), mem_fun(*this, &AdvEnvGUI::get_releaseTime3));
	m_scaleReleaseTime3 = new LabeledDial("Release Time 3", p_slotReleaseTime3, p_releaseTime3, 0, 1, NORMAL, 0.01, 2);
	p_releaseTimeWidget->pack_start(*m_scaleReleaseTime3);

	p_releaseTimeFrame->add(*p_releaseTimeWidget);
	p_mainWidget->pack_start(*p_releaseTimeFrame);


	p_mainWidget->pack_start(*(new HSeparator()));



	Frame *p_releaseLevelFrame = manage (new Frame("Release Level"));
	p_releaseLevelFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_releaseLevelWidget = manage (new HBox(false));

	slot<void> p_slotReleaseLevel1 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseLevel1), mem_fun(*this, &AdvEnvGUI::get_releaseLevel1));
	m_scaleReleaseLevel1 = new LabeledDial("Release Level 1", p_slotReleaseLevel1, p_releaseLevel1, 0, 1, NORMAL, 0.01, 2);
	p_releaseLevelWidget->pack_start(*m_scaleReleaseLevel1);

	slot<void> p_slotReleaseLevel2 = compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseLevel2), mem_fun(*this, &AdvEnvGUI::get_releaseLevel2));
	m_scaleReleaseLevel2 = new LabeledDial("Release Level 2", p_slotReleaseLevel2, p_releaseLevel2, 0, 1, NORMAL, 0.01, 2);
	p_releaseLevelWidget->pack_start(*m_scaleReleaseLevel2);

	p_releaseLevelFrame->add(*p_releaseLevelWidget);
	p_mainWidget->pack_start(*p_releaseLevelFrame);




	m_envScope->m_valueSustain = m_scaleSustain->get_value();
	m_envScope->m_valueDelay = m_scaleDelay->get_value();

	m_envScope->m_valueAttackTime1 = m_scaleAttackTime1->get_value();
	m_envScope->m_valueAttackTime2 = m_scaleAttackTime2->get_value();
	m_envScope->m_valueAttackTime3 = m_scaleAttackTime3->get_value();
	m_envScope->m_valueAttackTime4 = m_scaleAttackTime4->get_value();

	m_envScope->m_valueAttackLevel1 = m_scaleAttackLevel1->get_value();
	m_envScope->m_valueAttackLevel2 = m_scaleAttackLevel2->get_value();
	m_envScope->m_valueAttackLevel3 = m_scaleAttackLevel3->get_value();

	m_envScope->m_valueReleaseTime1 = m_scaleReleaseTime1->get_value();
	m_envScope->m_valueReleaseTime2 = m_scaleReleaseTime2->get_value();
	m_envScope->m_valueReleaseTime3 = m_scaleReleaseTime3->get_value();

	m_envScope->m_valueReleaseLevel1 = m_scaleReleaseLevel1->get_value();
	m_envScope->m_valueReleaseLevel2 = m_scaleReleaseLevel2->get_value();

	m_envScope->Redraw();




	p_mainWidget->set_size_request(350, 620);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float AdvEnvGUI::get_timeScale() { return m_scaleTimeScale->get_value(); }
float AdvEnvGUI::get_sustain() { return m_scaleSustain->get_value(); }
float AdvEnvGUI::get_delay() { return m_scaleDelay->get_value(); }

float AdvEnvGUI::get_attackTime1() { return m_scaleAttackTime1->get_value(); }
float AdvEnvGUI::get_attackTime2() { return m_scaleAttackTime2->get_value(); }
float AdvEnvGUI::get_attackTime3() { return m_scaleAttackTime3->get_value(); }
float AdvEnvGUI::get_attackTime4() { return m_scaleAttackTime4->get_value(); }

float AdvEnvGUI::get_attackLevel1() { return m_scaleAttackLevel1->get_value(); }
float AdvEnvGUI::get_attackLevel2() { return m_scaleAttackLevel2->get_value(); }
float AdvEnvGUI::get_attackLevel3() { return m_scaleAttackLevel3->get_value(); }

float AdvEnvGUI::get_releaseTime1() { return m_scaleReleaseTime1->get_value(); }
float AdvEnvGUI::get_releaseTime2() { return m_scaleReleaseTime2->get_value(); }
float AdvEnvGUI::get_releaseTime3() { return m_scaleReleaseTime3->get_value(); }

float AdvEnvGUI::get_releaseLevel1() { return m_scaleReleaseLevel1->get_value(); }
float AdvEnvGUI::get_releaseLevel2() { return m_scaleReleaseLevel2->get_value(); }

void AdvEnvGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_sustain)
	{
		m_valueSustain = *static_cast<const float*> (buffer);
		m_scaleSustain->set_value(m_valueSustain);
		m_envScope->m_valueSustain = m_valueSustain;
		m_envScope->Redraw();
	}
	else if (port == p_delay)
	{
		m_valueDelay = *static_cast<const float*> (buffer);
		m_scaleDelay->set_value(m_valueDelay);
		m_envScope->m_valueDelay = m_valueDelay;
		m_envScope->Redraw();
	}
	else if (port == p_attackTime1)
	{
		m_valueAttackTime1 = *static_cast<const float*> (buffer);
		m_scaleAttackTime1->set_value(m_valueAttackTime1);
		m_envScope->m_valueAttackTime1 = m_valueAttackTime1;
		m_envScope->Redraw();
	}
	else if (port == p_attackTime2)
	{
		m_valueAttackTime2 = *static_cast<const float*> (buffer);
		m_scaleAttackTime2->set_value(m_valueAttackTime2);
		m_envScope->m_valueAttackTime2 = m_valueAttackTime2;
		m_envScope->Redraw();
	}
	else if (port == p_attackTime3)
	{
		m_valueAttackTime3 = *static_cast<const float*> (buffer);
		m_scaleAttackTime3->set_value(m_valueAttackTime3);
		m_envScope->m_valueAttackTime3 = m_valueAttackTime3;
		m_envScope->Redraw();
	}
	else if (port == p_attackTime4)
	{
		m_valueAttackTime4 = *static_cast<const float*> (buffer);
		m_scaleAttackTime4->set_value(m_valueAttackTime4);
		m_envScope->m_valueAttackTime4 = m_valueAttackTime4;
		m_envScope->Redraw();
	}
	else if (port == p_attackLevel1)
	{
		m_valueAttackLevel1 = *static_cast<const float*> (buffer);
		m_scaleAttackLevel1->set_value(m_valueAttackLevel1);
		m_envScope->m_valueAttackLevel1 = m_valueAttackLevel1;
		m_envScope->Redraw();
	}
	else if (port == p_attackLevel2)
	{
		m_valueAttackLevel2 = *static_cast<const float*> (buffer);
		m_scaleAttackLevel2->set_value(m_valueAttackLevel2);
		m_envScope->m_valueAttackLevel2 = m_valueAttackLevel2;
		m_envScope->Redraw();
	}
	else if (port == p_attackLevel3)
	{
		m_valueAttackLevel3 = *static_cast<const float*> (buffer);
		m_scaleAttackLevel3->set_value(m_valueAttackLevel3);
		m_envScope->m_valueAttackLevel3 = m_valueAttackLevel3;
		m_envScope->Redraw();
	}
	else if (port == p_releaseTime1)
	{
		m_valueReleaseTime1 = *static_cast<const float*> (buffer);
		m_scaleReleaseTime1->set_value(m_valueReleaseTime1);
		m_envScope->m_valueReleaseTime1 = m_valueReleaseTime1;
		m_envScope->Redraw();
	}
	else if (port == p_releaseTime2)
	{
		m_valueReleaseTime2 = *static_cast<const float*> (buffer);
		m_scaleReleaseTime2->set_value(m_valueReleaseTime2);
		m_envScope->m_valueReleaseTime2 = m_valueReleaseTime2;
		m_envScope->Redraw();
	}
	else if (port == p_releaseTime3)
	{
		m_valueReleaseTime3 = *static_cast<const float*> (buffer);
		m_scaleReleaseTime3->set_value(m_valueReleaseTime3);
		m_envScope->m_valueReleaseTime3 = m_valueReleaseTime3;
		m_envScope->Redraw();
	}
	else if (port == p_releaseLevel1)
	{
		m_valueReleaseLevel1 = *static_cast<const float*> (buffer);
		m_scaleReleaseLevel1->set_value(m_valueReleaseLevel1);
		m_envScope->m_valueReleaseLevel1 = m_valueReleaseLevel1;
		m_envScope->Redraw();
	}
	else if (port == p_releaseLevel2)
	{
		m_valueReleaseLevel2 = *static_cast<const float*> (buffer);
		m_scaleReleaseLevel2->set_value(m_valueReleaseLevel2);
		m_envScope->m_valueReleaseLevel2 = m_valueReleaseLevel2;
		m_envScope->Redraw();
	}
	else if (port == p_timeScale)
	{
		m_scaleTimeScale->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = AdvEnvGUI::register_class("http://github.com/blablack/ams.lv2/advenv/gui");
