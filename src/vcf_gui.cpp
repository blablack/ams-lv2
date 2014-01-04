#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcf_gui.hpp"
#include "vcf.hpp"
#include "dial.hpp"
#include "my_box.hpp"

VcfGUI::VcfGUI(const std::string& URI)
{
    EventBox *p_background = manage(new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);


    VBox *p_mainWidget = manage(new VBox(false));


    MyBox *p_typeFrame = manage (new MyBox("Filter Type", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_comboVCFType = manage (new ComboBoxText());
    m_comboVCFType->append_text("Resonant Lowpass");
    m_comboVCFType->append_text("Lowpass");
    m_comboVCFType->append_text("Highpass");
    m_comboVCFType->append_text("Bandpass I");
    m_comboVCFType->append_text("Bandpass II");
    m_comboVCFType->append_text("Notch");
    m_comboVCFType->append_text("24dB Lowpass I");
    m_comboVCFType->append_text("24dB Lowpass II");
    m_comboVCFType->signal_changed().connect(compose(bind<0> (mem_fun(*this, &VcfGUI::write_control), p_vcfType), mem_fun(*m_comboVCFType, &ComboBoxText::get_active_row_number)));
    p_typeFrame->pack_start(*m_comboVCFType);

    p_mainWidget->pack_start(*p_typeFrame);


    MyBox *p_gainFrame = manage (new MyBox("Gain", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_scaleInputGain = new LabeledDial("Input", p_inputGain, 0, 10, LOG, 0.0001, 4);
    m_scaleInputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_inputGain), mem_fun(*m_scaleInputGain,  &LabeledDial::get_value)));
    p_gainFrame->pack_start(*m_scaleInputGain);

    m_scaleOutputGain = new LabeledDial("Output", p_outputGain, 0, 10, LOG, 0.0001, 4);
    m_scaleOutputGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_outputGain), mem_fun(*m_scaleOutputGain,  &LabeledDial::get_value)));
    p_gainFrame->pack_start(*m_scaleOutputGain);

    p_mainWidget->pack_start(*p_gainFrame);


    MyBox *p_freqFrame = manage(new MyBox("Frequency", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_scaleFrequency = new LabeledDial("Frequency", p_freq, 0, 10, LOG, 0.0001, 4);
    m_scaleFrequency->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_freq), mem_fun(*m_scaleFrequency,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleFrequency);

    m_scaleExpFMGain = new LabeledDial("Exp FM Gain", p_expFMGain, 0, 10, LOG, 0.0001, 4);
    m_scaleExpFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_expFMGain), mem_fun(*m_scaleExpFMGain,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleExpFMGain);

    m_scaleLinFMGain = new LabeledDial("Lin FM Gain", p_linFMGain, 0, 10, LOG, 0.0001, 4);
    m_scaleLinFMGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_linFMGain), mem_fun(*m_scaleLinFMGain,  &LabeledDial::get_value)));
    p_freqFrame->pack_start(*m_scaleLinFMGain);

    p_mainWidget->pack_start(*p_freqFrame);


    MyBox *p_resFrame = manage(new MyBox("Resonance", Gtk::Orientation::ORIENTATION_HORIZONTAL));

    m_scaleResonance = new LabeledDial("Resonance", p_resonance, 0.01, 1, LOG, 0.0001, 4);
    m_scaleResonance->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_resonance), mem_fun(*m_scaleResonance,  &LabeledDial::get_value)));
    p_resFrame->pack_start(*m_scaleResonance);

    m_scaleResonanceGain = new LabeledDial("Resonance Gain", p_resonanceGain, 0, 1, LOG, 0.0001, 4);
    m_scaleResonanceGain->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_resonanceGain), mem_fun(*m_scaleResonanceGain,  &LabeledDial::get_value)));
    p_resFrame->pack_start(*m_scaleResonanceGain);

    p_mainWidget->pack_start(*p_resFrame);


    p_background->add(*p_mainWidget);
    add(*p_background);

    Gtk::manage(p_mainWidget);
}

void VcfGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    int p_vcfTypeValue;

    switch(port)
    {
    case p_vcfType:
        p_vcfTypeValue = (int) (*static_cast<const float*> (buffer));
        if (p_vcfTypeValue >= 0 && p_vcfTypeValue <= 7)
            m_comboVCFType->set_active((int) p_vcfTypeValue);
        break;
    case p_inputGain:
        m_scaleInputGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_outputGain:
        m_scaleOutputGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_freq:
        m_scaleFrequency->set_value(*static_cast<const float*> (buffer));
        break;
    case p_resonance:
        m_scaleResonance->set_value(*static_cast<const float*> (buffer));
        break;
    case p_resonanceGain:
        m_scaleResonanceGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_expFMGain:
        m_scaleExpFMGain->set_value(*static_cast<const float*> (buffer));
        break;
    case p_linFMGain:
        m_scaleLinFMGain->set_value(*static_cast<const float*> (buffer));
        break;
    }
}

static int _ = VcfGUI::register_class("http://github.com/blablack/ams-lv2/vcf/gui");
