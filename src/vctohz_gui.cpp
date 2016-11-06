#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "vctohz.hpp"
#include "vctohz_ttl.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vctohz_gui.hpp"

VCToHZGUI::VCToHZGUI(const std::string& URI)
{
    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage (new VBox(false));


    MyBox *p_convFrame = manage (new MyBox("Conversion Mode", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboConversionMode = manage (new ComboBoxText());
    m_comboConversionMode->append_text("V/Octave --> Hz");
    m_comboConversionMode->append_text("V/Octave --> 0..1, 1=rate/2");
    m_comboConversionMode->append_text("V/Octave --> 0..1, 1=20000 Hz");
    m_comboConversionMode->signal_changed().connect(compose(bind<0> (mem_fun(*this, &VCToHZGUI::write_control), p_conversionMode), mem_fun(*m_comboConversionMode, &ComboBoxText::get_active_row_number)));

    p_convFrame->pack_start(*m_comboConversionMode);
    p_mainWidget->pack_start(*p_convFrame);


	m_dialOctaveOffset = new LabeledDial("Octave Offset", -3, 3, NORMAL, 0.01);
    m_dialOctaveOffset->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCToHZGUI::write_control), p_octaveOffset), mem_fun(*m_dialOctaveOffset, &LabeledDial::get_value)));
    p_mainWidget->pack_start(*m_dialOctaveOffset);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void VCToHZGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_conversionValue;

    switch(port)
    {
    case p_conversionMode:
        p_conversionValue = (int) (*static_cast<const float*> (buffer));
        if (p_conversionValue >= 0 && p_conversionValue <= 2)
            m_comboConversionMode->set_active((int) p_conversionValue);
        break;
    case p_octaveOffset:
        m_dialOctaveOffset->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = VCToHZGUI::register_class("http://github.com/blablack/ams-lv2/vctohz/gui");
