#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "mixer_4ch_gui.hpp"
#include "mixer_4ch.hpp"
#include "dial.hpp"

Mixer4ChGUI::Mixer4ChGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage(new VBox(false));


    m_dialGain = new LabeledDial("Gain", p_gain, 0, 2, NORMAL, 0.01, 2);
    m_dialGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChGUI::write_control), p_gain), mem_fun(*m_dialGain,  &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialGain);


    HBox *p_volumesFrame = manage(new HBox(true));

    m_dialVolume1 = new LabeledDial("Volume 1", p_volume1, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume1->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChGUI::write_control), p_volume1), mem_fun(*m_dialVolume1,  &LabeledDial::get_value)));
    p_volumesFrame->pack_start(*m_dialVolume1);

    m_dialVolume2 = new LabeledDial("Volume 2", p_volume2, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume2->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChGUI::write_control), p_volume2), mem_fun(*m_dialVolume2,  &LabeledDial::get_value)));
    p_volumesFrame->pack_start(*m_dialVolume2);

    m_dialVolume3 = new LabeledDial("Volume 3", p_volume3, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume3->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChGUI::write_control), p_volume3), mem_fun(*m_dialVolume3,  &LabeledDial::get_value)));
    p_volumesFrame->pack_start(*m_dialVolume3);

    m_dialVolume4 = new LabeledDial("Volume 4", p_volume4, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume4->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChGUI::write_control), p_volume4), mem_fun(*m_dialVolume4,  &LabeledDial::get_value)));
    p_volumesFrame->pack_start(*m_dialVolume4);

    p_mainWidget->pack_start(*p_volumesFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Mixer4ChGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    switch(port)
    {
    case p_gain:
        m_dialGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_volume1:
        m_dialVolume1->set_value(*static_cast<const float*> (buffer));
        break;
    case p_volume2:
        m_dialVolume2->set_value(*static_cast<const float*> (buffer));
        break;
    case p_volume3:
        m_dialVolume3->set_value(*static_cast<const float*> (buffer));
        break;
    case p_volume4:
        m_dialVolume4->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = Mixer4ChGUI::register_class("http://github.com/blablack/ams-lv2/mixer_4ch/gui");
