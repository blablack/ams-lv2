#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "noise2_cv_gui.hpp"
#include "noise2_cv.hpp"
#include "dial.hpp"

Noise2CVGUI::Noise2CVGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    VBox *p_mainWidget = manage (new VBox(false, 5));

    Label *p_labelWaveForm = manage (new Label("Noise Type"));
    p_mainWidget->pack_start(*p_labelWaveForm);

    m_comboNoiseForm = manage (new ComboBoxText());
    m_comboNoiseForm->append_text("White");
    m_comboNoiseForm->append_text("Random");
    m_comboNoiseForm->append_text("Pink");

    slot<void> p_slotNoiseForm = compose(bind<0> (mem_fun(*this, &Noise2CVGUI::write_control), p_noiseType), mem_fun(*m_comboNoiseForm, &ComboBoxText::get_active_row_number));
    m_comboNoiseForm->signal_changed().connect(p_slotNoiseForm);

    p_mainWidget->pack_start(*m_comboNoiseForm);

    m_dialRandomRate = new LabeledDial("Random Rate", p_rate, 0, 10, NORMAL, 0.01, 2);
    m_dialRandomRate->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Noise2CVGUI::write_control), p_rate), mem_fun(*m_dialRandomRate,  &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialRandomRate);

    m_dialRandomLevel = new LabeledDial("Random Level", p_level, 0, 1, LOG, 0.0001, 4);
    m_dialRandomLevel->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &Noise2CVGUI::write_control), p_level), mem_fun(*m_dialRandomLevel, &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialRandomLevel);

    p_mainWidget->set_size_request(150, 200);

    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void Noise2CVGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
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

static int _ = Noise2CVGUI::register_class("http://github.com/blablack/ams-lv2/noise2_cv/gui");
