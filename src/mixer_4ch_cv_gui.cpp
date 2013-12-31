#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "mixer_4ch_cv_gui.hpp"
#include "mixer_4ch_cv.hpp"
#include "dial.hpp"

Mixer4ChCVGUI::Mixer4ChCVGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);



    VBox *p_mainWidget = manage(new VBox(false, 5));



    m_dialGain = new LabeledDial("Gain", p_gain, 0, 2, NORMAL, 0.01, 2);
    m_dialGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChCVGUI::write_control), p_gain), mem_fun(*m_dialGain,  &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialGain);



    Frame *p_volumesFrame = manage(new Frame("Volumes"));
    p_volumesFrame->set_shadow_type(Gtk::SHADOW_NONE);
    Table *p_volumesBox = manage(new Table(2, 2, true));

    m_dialVolume1 = new LabeledDial("Volume 1", p_volume1, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume1->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChCVGUI::write_control), p_volume1), mem_fun(*m_dialVolume1,  &LabeledDial::get_value)));
    p_volumesBox->attach(*m_dialVolume1, 0, 1, 0, 1);

    m_dialVolume2 = new LabeledDial("Volume 2", p_volume2, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume2->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChCVGUI::write_control), p_volume2), mem_fun(*m_dialVolume2,  &LabeledDial::get_value)));
    p_volumesBox->attach(*m_dialVolume2, 1, 2, 0, 1);

    m_dialVolume3 = new LabeledDial("Volume 3", p_volume3, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume3->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChCVGUI::write_control), p_volume3), mem_fun(*m_dialVolume3,  &LabeledDial::get_value)));
    p_volumesBox->attach(*m_dialVolume3, 0, 1, 1, 2);

    m_dialVolume4 = new LabeledDial("Volume 4", p_volume4, 0, 2, NORMAL, 0.01, 2);
    m_dialVolume4->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Mixer4ChCVGUI::write_control), p_volume4), mem_fun(*m_dialVolume4,  &LabeledDial::get_value)));
    p_volumesBox->attach(*m_dialVolume4, 1, 2, 1, 2);

    p_volumesFrame->add(*p_volumesBox);
    p_mainWidget->pack_start(*p_volumesFrame);



    p_mainWidget->set_size_request(150, 300);

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Mixer4ChCVGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
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

static int _ = Mixer4ChCVGUI::register_class("http://github.com/blablack/ams-lv2/mixer_4ch_cv/gui");
