#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "vcorgan.hpp"

#if OSC_COUNT == 4
#include "vcorgan_4_ttl.hpp"
#elif OSC_COUNT == 6
#include "vcorgan_6_ttl.hpp"
#elif OSC_COUNT == 8
#include "vcorgan_8_ttl.hpp"
#endif

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "vcorgan_gui.hpp"

VCOrganGUI::VCOrganGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	Notebook *p_tabs = manage (new Notebook());
	p_tabs->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainPage = manage (new VBox(false));

	MyBox *p_tune_modulation = manage (new MyBox("Tune / Modulation", Gtk::Orientation::ORIENTATION_VERTICAL));

	HBox *p_tune_mod_tune = manage (new HBox(false));
	p_tune_mod_tune->pack_start(*(m_octave = CreateDial("Octave", p_octave, NORMAL, 1)));
	p_tune_mod_tune->pack_start(*(m_tune = CreateDial("Tune", p_tune, NORMAL, 0.01)));
	p_tune_modulation->pack_start(*p_tune_mod_tune);

	HBox *p_tune_mod_gain = manage (new HBox(false));
	p_tune_mod_gain->pack_start(*(m_expFMGain = CreateDial("Exp. FM Gain", p_expFMGain, NORMAL, 0.01)));
	p_tune_mod_gain->pack_start(*(m_linFMGain = CreateDial("Lin. FM Gain", p_linFMGain, NORMAL, 0.01)));
	p_tune_modulation->pack_start(*p_tune_mod_gain);

	p_mainPage->pack_start(*p_tune_modulation);

	MyBox *p_mixer = manage (new MyBox("Mixer", Gtk::Orientation::ORIENTATION_HORIZONTAL));
	for( int i = 0; i < MODULE_DYNAMICWAVES_OSC; i++ )
		p_mixer->pack_start(*(m_mixer[i] = CreateDial("Volume " + std::to_string(i+1), volume[i], NORMAL, 0.01)));
	p_mainPage->pack_start(*p_mixer);

	p_tabs->append_page(*p_mainPage, "Main");

	for( int i = 0; i < MODULE_DYNAMICWAVES_OSC; i++ )
	{
		VBox *p_vcoPage = manage (new VBox(false));

		MyBox *p_waveFormFrame = manage (new MyBox("Wave Form", Gtk::Orientation::ORIENTATION_HORIZONTAL));
		m_comboWaveForm[i] = manage (new ComboBoxText());
		m_comboWaveForm[i]->append_text("Sine");
		m_comboWaveForm[i]->append_text("Sawtooth");
		m_comboWaveForm[i]->append_text("Triangle");
		m_comboWaveForm[i]->append_text("Rectangle");
		m_comboWaveForm[i]->append_text("Saw 2");
		m_comboWaveForm[i]->signal_changed().connect(mem_fun(*this, &VCOrganGUI::get_waveform));
		p_waveFormFrame->pack_start(*m_comboWaveForm[i]);

		p_vcoPage->pack_start(*p_waveFormFrame);


		MyBox *p_freqFrame = manage(new MyBox("Frequency", Gtk::Orientation::ORIENTATION_HORIZONTAL));
		p_freqFrame->pack_start(*(m_scaleOctave[i]		= CreateDial("Octave", osc_octave[i], NORMAL, 1)));
		p_freqFrame->pack_start(*(m_scaleTune[i]		= CreateDial("Tune", osc_tune[i], NORMAL, 0.01)));
		p_freqFrame->pack_start(*(m_scaleHarmonic[i]	= CreateDial("Harmonic", harmonic[i], NORMAL, 1)));
		p_freqFrame->pack_start(*(m_scaleSubharmonic[i] = CreateDial("Subharmonic", subharmonic[i], NORMAL, 1)));
		p_vcoPage->pack_start(*p_freqFrame);


		p_vcoPage->pack_start(*(m_scalePhi0[i]			= CreateDial("Phi0", phi0[i], NORMAL, 0.01)));

		p_tabs->append_page(*p_vcoPage, "VCO " + std::to_string(i+1));
	}

	p_background->add(*p_tabs);
	add(*p_background);

	Gtk::manage(p_tabs);
}

void VCOrganGUI::get_waveform()
{
	for( int i = 0; i < MODULE_DYNAMICWAVES_OSC; i++ )
			this->write_control(waveForm[i], m_comboWaveForm[i]->get_active_row_number());
	}

LabeledDial* VCOrganGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &VCOrganGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

void VCOrganGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	switch( port )
	{
		case p_octave:
			m_octave->set_value(*static_cast<const float*> (buffer));
			break;
		case p_tune:
			m_tune->set_value(*static_cast<const float*> (buffer));
			break;
		case p_expFMGain:
			m_expFMGain->set_value(*static_cast<const float*> (buffer));
			break;
		case p_linFMGain:
			m_linFMGain->set_value(*static_cast<const float*> (buffer));
			break;
	}

	for( int i = 0 ; i < MODULE_DYNAMICWAVES_OSC ; i++ )
	{
		if( port == volume[i] )
			m_mixer[i]->set_value(*static_cast<const float*> (buffer));

		else if( port == waveForm[i] )
		{
			int p_waveFormValue = (int) (*static_cast<const float*> (buffer));
			if (p_waveFormValue >= 0 && p_waveFormValue <= 4)
				m_comboWaveForm[i]->set_active((int) p_waveFormValue);
		}
		else if( port == osc_octave[i] )
			m_scaleOctave[i]->set_value(*static_cast<const float*> (buffer));
		else if( port == osc_tune[i] )
			m_scaleTune[i]->set_value(*static_cast<const float*> (buffer));
		else if( port == harmonic[i] )
			m_scaleHarmonic[i]->set_value(*static_cast<const float*> (buffer));
		else if( port == subharmonic[i] )
			m_scaleSubharmonic[i]->set_value(*static_cast<const float*> (buffer));
		else if( port == phi0[i] )
			m_scalePhi0[i]->set_value(*static_cast<const float*> (buffer));
	}
}

#if OSC_COUNT == 4
	static int _ = VCOrganGUI::register_class("http://github.com/blablack/ams-lv2/vcorgan_4/gui");
#elif OSC_COUNT == 6
	static int _ = VCOrganGUI::register_class("http://github.com/blablack/ams-lv2/vcorgan_6/gui");
#elif OSC_COUNT == 8
	static int _ = VCOrganGUI::register_class("http://github.com/blablack/ams-lv2/vcorgan_8/gui");
#endif


