#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "seq.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "seq_gui.hpp"

SeqGUI::SeqGUI(const std::string& URI)
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

void SeqGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
}

#if STEP_COUNT == 8
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_8/gui");
#elif STEP_COUNT == 12
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_12/gui");
#elif STEP_COUNT == 16
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_16/gui");
#elif STEP_COUNT == 24
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_24/gui");
#elif STEP_COUNT == 32
static int _ = SeqGUI::register_class("http://github.com/blablack/ams-lv2/seq_32/gui");
#endif



