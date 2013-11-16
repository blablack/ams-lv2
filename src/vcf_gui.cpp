#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcf_gui.hpp"
#include "vcf.hpp"
#include "dial.hpp"

VcfGUI::VcfGUI(const std::string& URI)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);



	VBox *p_mainWidget = manage(new VBox(false, 5));


	Label *p_labeFilterType = manage (new Label("Filter Type"));
	p_mainWidget->pack_start(*p_labeFilterType);

	m_comboVCFType = manage (new ComboBoxText());
	m_comboVCFType->append_text("Resonant Lowpass");
	m_comboVCFType->append_text("Lowpass");
	m_comboVCFType->append_text("Highpass");
	m_comboVCFType->append_text("Bandpass I");
	m_comboVCFType->append_text("Bandpass II");
	m_comboVCFType->append_text("Notch");
	m_comboVCFType->append_text("24dB Lowpass I");
	m_comboVCFType->append_text("24dB Lowpass II");

	slot<void> p_slotVCFType = compose(bind<0> (mem_fun(*this, &VcfGUI::write_control), p_vcfType), mem_fun(*m_comboVCFType, &ComboBoxText::get_active_row_number));
	m_comboVCFType->signal_changed().connect(p_slotVCFType);
	p_mainWidget->pack_start(*m_comboVCFType);



	slot<void> p_slotGain = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_inputGain), mem_fun(*this,  &VcfGUI::get_inputGain));
	m_scaleInputGain = new LabeledDial("Input Gain", p_slotGain, p_inputGain, 0, 10, LOG, 0.0001, 4);
	p_mainWidget->pack_start(*m_scaleInputGain);



	Frame *p_freqFrame = manage(new Frame("Frequency"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_freqBox = manage(new HBox(true));

	slot<void> p_slotFrequency = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_freq), mem_fun(*this,  &VcfGUI::get_frequency));
	m_scaleFrequency = new LabeledDial("Frequency", p_slotFrequency, p_freq, 0, 10, LOG, 0.0001, 4);
	p_freqBox->pack_start(*m_scaleFrequency);

	slot<void> p_slotExpFMGain = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_expFMGain), mem_fun(*this,  &VcfGUI::get_expFMGain));
	m_scaleExpFMGain = new LabeledDial("Exp FM Gain", p_slotExpFMGain, p_expFMGain, 0, 10, LOG, 0.0001, 4);
	p_freqBox->pack_start(*m_scaleExpFMGain);

	slot<void> p_slotLinFMGain = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_linFMGain), mem_fun(*this,  &VcfGUI::get_linFMGain));
	m_scaleLinFMGain = new LabeledDial("Lin FM Gain", p_slotLinFMGain, p_linFMGain, 0, 10, LOG, 0.0001, 4);
	p_freqBox->pack_start(*m_scaleLinFMGain);

	p_freqFrame->add(*p_freqBox);
	p_mainWidget->pack_start(*p_freqFrame);



	Frame *p_resFrame = manage(new Frame("Resonance"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_resBox = manage(new HBox(true));

	slot<void> p_slotResonance = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_resonance), mem_fun(*this,  &VcfGUI::get_resonance));
	m_scaleResonance = new LabeledDial("Resonance", p_slotResonance, p_resonance, 0.01, 1, LOG, 0.0001, 4);
	p_resBox->pack_start(*m_scaleResonance);

	slot<void> p_slotResonanceGain = compose(bind<0>(mem_fun(*this, &VcfGUI::write_control), p_resonanceGain), mem_fun(*this,  &VcfGUI::get_resonanceGain));
	m_scaleResonanceGain = new LabeledDial("Resonance Gain", p_slotResonanceGain, p_resonanceGain, 0, 1, LOG, 0.0001, 4);
	p_resBox->pack_start(*m_scaleResonanceGain);

	p_resFrame->add(*p_resBox);
	p_mainWidget->pack_start(*p_resFrame);



	p_mainWidget->set_size_request(180, 310);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float VcfGUI::get_inputGain() 		{ return m_scaleInputGain->get_value(); }
float VcfGUI::get_frequency() 		{ return m_scaleFrequency->get_value(); }
float VcfGUI::get_expFMGain() 		{ return m_scaleExpFMGain->get_value(); }
float VcfGUI::get_linFMGain() 		{ return m_scaleLinFMGain->get_value(); }
float VcfGUI::get_resonance() 		{ return m_scaleResonance->get_value(); }
float VcfGUI::get_resonanceGain() 	{ return m_scaleResonanceGain->get_value(); }

void VcfGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_vcfType)
	{
		int p_vcfTypeValue = (int) (*static_cast<const float*> (buffer));
		if (p_vcfTypeValue >= 0 && p_vcfTypeValue <= 7)
		{
			m_comboVCFType->set_active((int) p_vcfTypeValue);
		}
	}
	else if (port == p_inputGain)
	{
		m_scaleInputGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_freq)
	{
		m_scaleFrequency->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_resonance)
	{
		m_scaleResonance->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_resonanceGain)
	{
		m_scaleResonanceGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_expFMGain)
	{
		m_scaleExpFMGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_linFMGain)
	{
		m_scaleLinFMGain->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = VcfGUI::register_class("http://github.com/blablack/ams.lv2/vcf/gui");
