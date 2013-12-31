#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcpanning_gui.hpp"
#include "vcpanning.hpp"
#include "dial.hpp"

VcPanningGUI::VcPanningGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false, 5));

    Label *p_labelPanningMode = manage (new Label("Panning Mode"));
    p_mainWidget->pack_start(*p_labelPanningMode);

    m_comboPanningMode = manage (new ComboBoxText());
    m_comboPanningMode->append_text("VC Control");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Full Width");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Half Width");
    m_comboPanningMode->append_text("Fixed Alternating Panorama - Quarter Width");
    m_comboPanningMode->append_text("Mono");

    m_comboPanningMode->signal_changed().connect(compose(bind<0> (mem_fun(*this, &VcPanningGUI::write_control), p_panningMode), mem_fun(*m_comboPanningMode, &ComboBoxText::get_active_row_number)));

    p_mainWidget->pack_start(*m_comboPanningMode);

    HBox *p_dials = manage (new HBox(true));

    m_scalePanOffset = new LabeledDial("Pan Offset", p_panOffset, -1, 1, NORMAL, 0.01, 2);
    m_scalePanOffset->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcPanningGUI::write_control), p_panOffset), mem_fun(*m_scalePanOffset,  &LabeledDial::get_value)));
    p_dials->pack_start(*m_scalePanOffset);

    m_scalePanGain = new LabeledDial("Pain Gain", p_panGain, 0, 2, LOG, 0.0001, 4);
    m_scalePanGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcPanningGUI::write_control), p_panGain), mem_fun(*m_scalePanGain, &LabeledDial::get_value)));
    p_dials->pack_start(*m_scalePanGain);

    p_mainWidget->pack_start(*p_dials);

    p_mainWidget->set_size_request(256, 160);

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
