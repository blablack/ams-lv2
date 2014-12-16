#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "slew.hpp"
#include "slew_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "slew_gui.hpp"

SlewGUI::SlewGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

	m_dialTimeUp = new LabeledDial("Time Up", 0, 10, NORMAL, 0.1);
    m_dialTimeUp->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &SlewGUI::write_control), p_timeUp), mem_fun(*m_dialTimeUp,  &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialTimeUp);

	m_dialTimeDown = new LabeledDial("Time Down", 0, 10, NORMAL, 0.1);
    m_dialTimeDown->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &SlewGUI::write_control), p_timeDown), mem_fun(*m_dialTimeDown, &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialTimeDown);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void SlewGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_timeUp:
        m_dialTimeUp->set_value(*static_cast<const float*> (buffer));
        break;
    case p_timeDown:
        m_dialTimeDown->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = SlewGUI::register_class("http://github.com/blablack/ams-lv2/slew/gui");
