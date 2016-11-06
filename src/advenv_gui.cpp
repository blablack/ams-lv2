#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "advenv.hpp"
#include "advenv_gui_scope.hpp"
#include "advenv_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "advenv_gui.hpp"

AdvEnvGUI::AdvEnvGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    m_envScope = new AdvEnvGUIScope();
    p_mainWidget->pack_start(*m_envScope);




    MyBox *p_scaleFrame = manage (new MyBox("Time Scale / Sustain / Delay", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleTimeScale = new LabeledDial("Time Scale", 0.1, 10, NORMAL, 0.01);
    m_scaleTimeScale->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &AdvEnvGUI::write_control), p_timeScale), mem_fun(*m_scaleTimeScale, &LabeledDial::get_value)));
    p_scaleFrame->pack_start(*m_scaleTimeScale);

	m_scaleSustain = new LabeledDial("Sustain", 0, 1, NORMAL, 0.01);
    m_scaleSustain->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_sustain), mem_fun(*m_scaleSustain, &LabeledDial::get_value)));
    p_scaleFrame->pack_start(*m_scaleSustain);

	m_scaleDelay = new LabeledDial("Delay", 0, 1, NORMAL, 0.01);
    m_scaleDelay->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_delay), mem_fun(*m_scaleDelay, &LabeledDial::get_value)));
    p_scaleFrame->pack_start(*m_scaleDelay);

    p_mainWidget->pack_start(*p_scaleFrame);


    MyBox *p_attackTimeFrame = manage (new MyBox("Attack Time", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleAttackTime1 = new LabeledDial("Time 1", 0, 1, NORMAL, 0.01);
    m_scaleAttackTime1->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime1), mem_fun(*m_scaleAttackTime1, &LabeledDial::get_value)));
    p_attackTimeFrame->pack_start(*m_scaleAttackTime1);

	m_scaleAttackTime2 = new LabeledDial("Time 2", 0, 1, NORMAL, 0.01);
    m_scaleAttackTime2->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime2), mem_fun(*m_scaleAttackTime2, &LabeledDial::get_value)));
    p_attackTimeFrame->pack_start(*m_scaleAttackTime2);

	m_scaleAttackTime3 = new LabeledDial("Time 3", 0, 1, NORMAL, 0.01);
    m_scaleAttackTime3->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime3), mem_fun(*m_scaleAttackTime3, &LabeledDial::get_value)));
    p_attackTimeFrame->pack_start(*m_scaleAttackTime3);

	m_scaleAttackTime4 = new LabeledDial("Time 4", 0, 1, NORMAL, 0.01);
    m_scaleAttackTime4->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackTime4), mem_fun(*m_scaleAttackTime4, &LabeledDial::get_value)));
    p_attackTimeFrame->pack_start(*m_scaleAttackTime4);

    p_mainWidget->pack_start(*p_attackTimeFrame);


    MyBox *p_attackLevelFrame = manage (new MyBox("Attack Level", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleAttackLevel1 = new LabeledDial("Level 1", 0, 1, NORMAL, 0.01);
    m_scaleAttackLevel1->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel1), mem_fun(*m_scaleAttackLevel1, &LabeledDial::get_value)));
    p_attackLevelFrame->pack_start(*m_scaleAttackLevel1);

	m_scaleAttackLevel2 = new LabeledDial("Level 2", 0, 1, NORMAL, 0.01);
    m_scaleAttackLevel2->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel2), mem_fun(*m_scaleAttackLevel2, &LabeledDial::get_value)));
    p_attackLevelFrame->pack_start(*m_scaleAttackLevel2);

	m_scaleAttackLevel3 = new LabeledDial("Level 3", 0, 1, NORMAL, 0.01);
    m_scaleAttackLevel3->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_attackLevel3), mem_fun(*m_scaleAttackLevel3, &LabeledDial::get_value)));
    p_attackLevelFrame->pack_start(*m_scaleAttackLevel3);

    p_mainWidget->pack_start(*p_attackLevelFrame);


    MyBox *p_releaseTimeFrame = manage (new MyBox("Release Time", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleReleaseTime1 = new LabeledDial("Time 1", 0, 1, NORMAL, 0.01);
    m_scaleReleaseTime1->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime1), mem_fun(*m_scaleReleaseTime1, &LabeledDial::get_value)));
    p_releaseTimeFrame->pack_start(*m_scaleReleaseTime1);

	m_scaleReleaseTime2 = new LabeledDial("Time 2", 0, 1, NORMAL, 0.01);
    m_scaleReleaseTime2->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime2), mem_fun(*m_scaleReleaseTime2, &LabeledDial::get_value)));
    p_releaseTimeFrame->pack_start(*m_scaleReleaseTime2);

	m_scaleReleaseTime3 = new LabeledDial("Time 3", 0, 1, NORMAL, 0.01);
    m_scaleReleaseTime3->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseTime3), mem_fun(*m_scaleReleaseTime3, &LabeledDial::get_value)));
    p_releaseTimeFrame->pack_start(*m_scaleReleaseTime3);

    p_mainWidget->pack_start(*p_releaseTimeFrame);


    MyBox *p_releaseLevelFrame = manage (new MyBox("Release Level", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleReleaseLevel1 = new LabeledDial("Level 1", 0, 1, NORMAL, 0.01);
    m_scaleReleaseLevel1->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseLevel1), mem_fun(*m_scaleReleaseLevel1, &LabeledDial::get_value)));
    p_releaseLevelFrame->pack_start(*m_scaleReleaseLevel1);

	m_scaleReleaseLevel2 = new LabeledDial("Level 2", 0, 1, NORMAL, 0.01);
    m_scaleReleaseLevel2->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &AdvEnvGUI::write_control), p_releaseLevel2), mem_fun(*m_scaleReleaseLevel2, &LabeledDial::get_value)));
    p_releaseLevelFrame->pack_start(*m_scaleReleaseLevel2);

    p_mainWidget->pack_start(*p_releaseLevelFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void AdvEnvGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_sustain:
        m_valueSustain = *static_cast<const float*> (buffer);
        m_scaleSustain->set_value(m_valueSustain);
        m_envScope->m_valueSustain = m_valueSustain;
        m_envScope->Redraw();
        break;
    case p_delay:
        m_valueDelay = *static_cast<const float*> (buffer);
        m_scaleDelay->set_value(m_valueDelay);
        m_envScope->m_valueDelay = m_valueDelay;
        m_envScope->Redraw();
        break;
    case p_attackTime1:
        m_valueAttackTime1 = *static_cast<const float*> (buffer);
        m_scaleAttackTime1->set_value(m_valueAttackTime1);
        m_envScope->m_valueAttackTime1 = m_valueAttackTime1;
        m_envScope->Redraw();
        break;
    case p_attackTime2:
        m_valueAttackTime2 = *static_cast<const float*> (buffer);
        m_scaleAttackTime2->set_value(m_valueAttackTime2);
        m_envScope->m_valueAttackTime2 = m_valueAttackTime2;
        m_envScope->Redraw();
        break;
    case p_attackTime3:
        m_valueAttackTime3 = *static_cast<const float*> (buffer);
        m_scaleAttackTime3->set_value(m_valueAttackTime3);
        m_envScope->m_valueAttackTime3 = m_valueAttackTime3;
        m_envScope->Redraw();
        break;
    case p_attackTime4:
        m_valueAttackTime4 = *static_cast<const float*> (buffer);
        m_scaleAttackTime4->set_value(m_valueAttackTime4);
        m_envScope->m_valueAttackTime4 = m_valueAttackTime4;
        m_envScope->Redraw();
        break;
    case p_attackLevel1:
        m_valueAttackLevel1 = *static_cast<const float*> (buffer);
        m_scaleAttackLevel1->set_value(m_valueAttackLevel1);
        m_envScope->m_valueAttackLevel1 = m_valueAttackLevel1;
        m_envScope->Redraw();
        break;
    case p_attackLevel2:
        m_valueAttackLevel2 = *static_cast<const float*> (buffer);
        m_scaleAttackLevel2->set_value(m_valueAttackLevel2);
        m_envScope->m_valueAttackLevel2 = m_valueAttackLevel2;
        m_envScope->Redraw();
        break;
    case p_attackLevel3:
        m_valueAttackLevel3 = *static_cast<const float*> (buffer);
        m_scaleAttackLevel3->set_value(m_valueAttackLevel3);
        m_envScope->m_valueAttackLevel3 = m_valueAttackLevel3;
        m_envScope->Redraw();
        break;
    case p_releaseTime1:
        m_valueReleaseTime1 = *static_cast<const float*> (buffer);
        m_scaleReleaseTime1->set_value(m_valueReleaseTime1);
        m_envScope->m_valueReleaseTime1 = m_valueReleaseTime1;
        m_envScope->Redraw();
        break;
    case p_releaseTime2:
        m_valueReleaseTime2 = *static_cast<const float*> (buffer);
        m_scaleReleaseTime2->set_value(m_valueReleaseTime2);
        m_envScope->m_valueReleaseTime2 = m_valueReleaseTime2;
        m_envScope->Redraw();
        break;
    case p_releaseTime3:
        m_valueReleaseTime3 = *static_cast<const float*> (buffer);
        m_scaleReleaseTime3->set_value(m_valueReleaseTime3);
        m_envScope->m_valueReleaseTime3 = m_valueReleaseTime3;
        m_envScope->Redraw();
        break;
    case p_releaseLevel1:
        m_valueReleaseLevel1 = *static_cast<const float*> (buffer);
        m_scaleReleaseLevel1->set_value(m_valueReleaseLevel1);
        m_envScope->m_valueReleaseLevel1 = m_valueReleaseLevel1;
        m_envScope->Redraw();
        break;
    case p_releaseLevel2:
        m_valueReleaseLevel2 = *static_cast<const float*> (buffer);
        m_scaleReleaseLevel2->set_value(m_valueReleaseLevel2);
        m_envScope->m_valueReleaseLevel2 = m_valueReleaseLevel2;
        m_envScope->Redraw();
        break;
    case p_timeScale:
        m_scaleTimeScale->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = AdvEnvGUI::register_class("http://github.com/blablack/ams-lv2/advenv/gui");
