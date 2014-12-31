#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

#include "hysteresis.hpp"
#include "hysteresis_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "hysteresis_gui.hpp"

HysteresisGUI::HysteresisGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void HysteresisGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{

}

static int _ = HysteresisGUI::register_class("http://github.com/blablack/ams-lv2/hysteresis/gui");
