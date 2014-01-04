#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "noise2_audio_gui.hpp"
#include "noise2_audio.hpp"
#include "dial.hpp"
#include "my_box.hpp"

Noise2AudioGUI::Noise2AudioGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false));

    MyBox *p_noiseTypeBox = manage (new MyBox("Noise Type", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboNoiseForm = manage (new ComboBoxText());
    m_comboNoiseForm->append_text("White");
    m_comboNoiseForm->append_text("Random");
    m_comboNoiseForm->append_text("Pink");
    m_comboNoiseForm->signal_changed().connect(compose(bind<0> (mem_fun(*this, &Noise2AudioGUI::write_control), p_noiseType), mem_fun(*m_comboNoiseForm, &ComboBoxText::get_active_row_number)));
    p_noiseTypeBox->pack_start(*m_comboNoiseForm);

    p_mainWidget->pack_start(*p_noiseTypeBox);


    MyBox *p_randomBox = manage(new MyBox("Random", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_dialRandomRate = new LabeledDial("Rate", p_rate, 0, 10, NORMAL, 0.01, 2);
    m_dialRandomRate->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Noise2AudioGUI::write_control), p_rate), mem_fun(*m_dialRandomRate,  &LabeledDial::get_value)));
    p_randomBox->pack_start(*m_dialRandomRate);

    m_dialRandomLevel = new LabeledDial("Level", p_level, 0, 1, LOG, 0.0001, 4);
    m_dialRandomLevel->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Noise2AudioGUI::write_control), p_level), mem_fun(*m_dialRandomLevel, &LabeledDial::get_value)));
    p_randomBox->pack_start(*m_dialRandomLevel);

    p_mainWidget->pack_start(*p_randomBox);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Noise2AudioGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_noiseFormValue;

    switch(port)
    {
    case p_noiseType:
        p_noiseFormValue = (int) (*static_cast<const float*> (buffer));
        if (p_noiseFormValue >= 0 && p_noiseFormValue <= 2)
            m_comboNoiseForm->set_active((int) p_noiseFormValue);
        break;
    case p_rate:
        m_dialRandomRate->set_value(*static_cast<const float*> (buffer));
        break;
    case p_level:
        m_dialRandomLevel->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = Noise2AudioGUI::register_class("http://github.com/blablack/ams-lv2/noise2_audio/gui");
