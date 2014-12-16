#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "percussiveenv.hpp"
#include "percussiveenv_gui_scope.hpp"
#include "percussiveenv_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "percussiveenv_gui.hpp"

PercussiveEnvGUI::PercussiveEnvGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    m_envScope = new PercussiveEnvGUIScope();
    p_mainWidget->pack_start(*m_envScope);



    MyBox *p_adsrFrame = manage (new MyBox("Attack / Delay", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleAttack = new LabeledDial("Attack", 0, 1, NORMAL, 0.01);
    m_scaleAttack->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &PercussiveEnvGUI::write_control), p_attack), mem_fun(*m_scaleAttack, &LabeledDial::get_value)));
    p_adsrFrame->pack_start(*m_scaleAttack);

	m_scaleDecay = new LabeledDial("Decay", 0, 1, NORMAL, 0.01);
    m_scaleDecay->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_decay), mem_fun(*m_scaleDecay, &LabeledDial::get_value)));
    p_adsrFrame->pack_start(*m_scaleDecay);

    p_mainWidget->pack_start(*p_adsrFrame);


    MyBox *p_dhtFrame = manage (new MyBox("Delay / Hold / Time Scale", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scaleDelay = new LabeledDial("Delay", 0, 1, NORMAL, 0.01);
    m_scaleDelay->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &PercussiveEnvGUI::write_control), p_delay), mem_fun(*m_scaleDelay, &LabeledDial::get_value)));
    p_dhtFrame->pack_start(*m_scaleDelay);

	m_scaleHold = new LabeledDial("Hold", 0, 1, NORMAL, 0.01);
    m_scaleHold->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_hold), mem_fun(*m_scaleHold, &LabeledDial::get_value)));
    p_dhtFrame->pack_start(*m_scaleHold);

	m_scaleTimeScale = new LabeledDial("Time Scale", 0, 10, NORMAL, 0.01);
    m_scaleTimeScale->signal_value_changed().connect(compose(bind<0> (mem_fun(*this, &PercussiveEnvGUI::write_control), p_timeScale), mem_fun(*m_scaleTimeScale, &LabeledDial::get_value)));
    p_dhtFrame->pack_start(*m_scaleTimeScale);

    p_mainWidget->pack_start(*p_dhtFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void PercussiveEnvGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
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

static int _ = PercussiveEnvGUI::register_class("http://github.com/blablack/ams-lv2/percussiveenv/gui");
