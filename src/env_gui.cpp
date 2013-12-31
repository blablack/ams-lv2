#include <gtkmm-2.4/gtkmm.h>
#include <gdkmm-2.4/gdkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "env_gui.hpp"
#include "env_gui_scope.hpp"
#include "env.hpp"
#include "dial.hpp"

EnvGUI::EnvGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false, 5));

    m_envScope = new EnvGUIScope();
    p_mainWidget->pack_start(*m_envScope);



    Frame *p_adsrFrame = manage (new Frame("ADSR"));
    p_adsrFrame->set_shadow_type(Gtk::SHADOW_NONE);
    HBox *p_adsrWidget = manage (new HBox(false));

    m_scaleAttack = new LabeledDial("Attack", p_attack, 0, 1, NORMAL, 0.01, 2);
    m_scaleAttack->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &EnvGUI::write_control), p_attack), mem_fun(*m_scaleAttack, &LabeledDial::get_value)));
    p_adsrWidget->pack_start(*m_scaleAttack);

    m_scaleDecay = new LabeledDial("Decay", p_decay, 0, 1, NORMAL, 0.01, 2);
    m_scaleDecay->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &EnvGUI::write_control), p_decay), mem_fun(*m_scaleDecay, &LabeledDial::get_value)));
    p_adsrWidget->pack_start(*m_scaleDecay);

    m_scaleSustain = new LabeledDial("Sustain", p_delay, 0, 1, NORMAL, 0.01, 2);
    m_scaleSustain->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &EnvGUI::write_control), p_sustain), mem_fun(*m_scaleSustain, &LabeledDial::get_value)));
    p_adsrWidget->pack_start(*m_scaleSustain);

    m_scaleRelease = new LabeledDial("Release", p_release, 0, 1, NORMAL, 0.01, 2);
    m_scaleRelease->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &EnvGUI::write_control), p_release), mem_fun(*m_scaleRelease, &LabeledDial::get_value)));
    p_adsrWidget->pack_start(*m_scaleRelease);

    p_adsrFrame->add(*p_adsrWidget);
    p_mainWidget->pack_start(*p_adsrFrame);



    p_mainWidget->pack_start(*(new HSeparator()));



    Frame *p_dhtFrame = manage (new Frame("Delay / Hold / Time Scale"));
    p_dhtFrame->set_shadow_type(Gtk::SHADOW_NONE);
    HBox *p_dhtWidget = manage (new HBox(false));

    m_scaleDelay = new LabeledDial("Delay", p_delay, 0, 1, NORMAL, 0.01, 2);
    m_scaleDelay->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &EnvGUI::write_control), p_delay), mem_fun(*m_scaleDelay, &LabeledDial::get_value)));
    p_dhtWidget->pack_start(*m_scaleDelay);

    m_scaleHold = new LabeledDial("Hold", p_hold, 0, 1, NORMAL, 0.01, 2);
    m_scaleHold->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &EnvGUI::write_control), p_hold), mem_fun(*m_scaleHold, &LabeledDial::get_value)));
    p_dhtWidget->pack_start(*m_scaleHold);

    m_scaleTimeScale = new LabeledDial("Time Scale", p_timeScale, 0, 10, NORMAL, 0.01, 2);
    m_scaleTimeScale->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &EnvGUI::write_control), p_timeScale), mem_fun(*m_scaleTimeScale, &LabeledDial::get_value)));
    p_dhtWidget->pack_start(*m_scaleTimeScale);

    p_dhtFrame->add(*p_dhtWidget);
    p_mainWidget->pack_start(*p_dhtFrame);



    m_envScope->m_attackValue = m_scaleAttack->get_value();
    m_envScope->m_decayValue = m_scaleDecay->get_value();
    m_envScope->m_sustainValue = m_scaleSustain->get_value();
    m_envScope->m_releaseValue = m_scaleRelease->get_value();
    m_envScope->m_delayValue = m_scaleDelay->get_value();
    m_envScope->m_holdValue = m_scaleHold->get_value();

    m_envScope->Redraw();



    p_mainWidget->set_size_request(200, 320);

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void EnvGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_attack:
        m_attackValue = *static_cast<const float*> (buffer);
        m_scaleAttack->set_value(m_attackValue);
        m_envScope->m_attackValue = m_attackValue;
        m_envScope->Redraw();
        break;
    case p_decay:
        m_decayValue = *static_cast<const float*> (buffer);
        m_scaleDecay->set_value(m_decayValue);
        m_envScope->m_decayValue = m_decayValue;
        m_envScope->Redraw();
        break;
    case p_sustain:
        m_sustainValue = *static_cast<const float*> (buffer);
        m_scaleSustain->set_value(m_sustainValue);
        m_envScope->m_sustainValue = m_sustainValue;
        m_envScope->Redraw();
        break;
    case p_release:
        m_releaseValue = *static_cast<const float*> (buffer);
        m_scaleRelease->set_value(m_releaseValue);
        m_envScope->m_releaseValue = m_releaseValue;
        m_envScope->Redraw();
        break;
    case p_delay:
        m_delayValue = *static_cast<const float*> (buffer);
        m_scaleDelay->set_value(m_delayValue);
        m_envScope->m_delayValue = m_delayValue;
        m_envScope->Redraw();
        break;
    case p_hold:
        m_holdValue = *static_cast<const float*> (buffer);
        m_scaleHold->set_value(m_holdValue);
        m_envScope->m_holdValue = m_holdValue;
        m_envScope->Redraw();
        break;
    case p_timeScale:
        m_scaleTimeScale->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = EnvGUI::register_class("http://github.com/blablack/ams-lv2/env/gui");
