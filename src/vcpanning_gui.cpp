#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "vcpanning.hpp"
#include "vcpanning_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vcpanning_gui.hpp"

VcPanningGUI::VcPanningGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage (new VBox(false));


    MyBox *p_modeFrame = manage (new MyBox("Panning Mode", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboPanningMode = manage (new ComboBoxText());
    m_comboPanningMode->append_text("VC Control");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Full Width");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Half Width");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Quarter Width");
    m_comboPanningMode->append_text("Mono");
    m_comboPanningMode->signal_changed().connect(compose(bind<0> (mem_fun(*this, &VcPanningGUI::write_control), p_panningMode), mem_fun(*m_comboPanningMode, &ComboBoxText::get_active_row_number)));

    p_modeFrame->pack_start(*m_comboPanningMode);
    p_mainWidget->pack_start(*p_modeFrame);


    MyBox *p_panFrame = manage (new MyBox("Panning", Gtk::Orientation::ORIENTATION_HORIZONTAL));

	m_scalePanOffset = new LabeledDial("Pan Offset", -1, 1, NORMAL, 0.01);
    m_scalePanOffset->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcPanningGUI::write_control), p_panOffset), mem_fun(*m_scalePanOffset,  &LabeledDial::get_value)));
    p_panFrame->pack_start(*m_scalePanOffset);

	m_scalePanGain = new LabeledDial("Pan Gain", 0, 2, LOG, 0.0001);
    m_scalePanGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcPanningGUI::write_control), p_panGain), mem_fun(*m_scalePanGain, &LabeledDial::get_value)));
    p_panFrame->pack_start(*m_scalePanGain);

    p_mainWidget->pack_start(*p_panFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void VcPanningGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_panningModeValue;

    switch(port)
    {
    case p_panningMode:
        p_panningModeValue = (int) (*static_cast<const float*> (buffer));
        if (p_panningModeValue >= 0 && p_panningModeValue <= 4)
            m_comboPanningMode->set_active((int) p_panningModeValue);
        break;
    case p_panOffset:
        m_scalePanOffset->set_value(*static_cast<const float*> (buffer));
        break;
    case p_panGain:
        m_scalePanGain->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = VcPanningGUI::register_class("http://github.com/blablack/ams-lv2/vcpanning/gui");
