#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"
#include "my_box.hpp"

#include "dynamicwaves.hpp"
#include "dynamicwaves_scope.hpp"

#if OSC_COUNT == 4
#include "dynamicwaves_4_ttl.hpp"
#elif OSC_COUNT == 6
#include "dynamicwaves_6_ttl.hpp"
#elif OSC_COUNT == 8
#include "dynamicwaves_8_ttl.hpp"
#endif

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "dynamicwaves_gui.hpp"

DynamicWavesGUI::DynamicWavesGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	Notebook *p_tabs = manage (new Notebook());
	p_tabs->modify_bg(Gtk::STATE_NORMAL, *color);

	VBox *p_mainPage = manage (new VBox(false));

	m_envScope[0] = new DynamicWavesScope(MODULE_DYNAMICWAVES_OSC);
	p_mainPage->pack_start(*m_envScope[0]);

	MyBox *p_tune_modulation = manage (new MyBox("Tune / Modulation", Gtk::Orientation::ORIENTATION_VERTICAL));

	HBox *p_tune_mod_tune = manage (new HBox(false));
	p_tune_mod_tune->pack_start(*(m_octave = CreateDial("Octave", p_octave, NORMAL, 1)));
	p_tune_mod_tune->pack_start(*(m_tune = CreateDial("Tune", p_tune, NORMAL, 0.01)));
	p_tune_modulation->pack_start(*p_tune_mod_tune);

	HBox *p_tune_mod_gain = manage (new HBox(false));
	p_tune_mod_gain->pack_start(*(m_expFMGain = CreateDial("Exp. FM Gain", p_expFMGain, NORMAL, 0.01)));
	p_tune_mod_gain->pack_start(*(m_linFMGain = CreateDial("Lin. FM Gain", p_linFMGain, NORMAL, 0.01)));
	p_tune_modulation->pack_start(*p_tune_mod_gain);

	p_tune_modulation->pack_start(*(m_timescale = CreateDial("Timescale", p_timeScale, LOG, 0.01)));

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
		m_comboWaveForm[i]->signal_changed().connect(mem_fun(*this, &DynamicWavesGUI::get_waveform));
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

	for( int i = 0; i < MODULE_DYNAMICWAVES_OSC; i++ )
	{
		VBox *p_envPage = manage (new VBox(false));

		p_envPage->pack_start(*(m_envScope[i+1] = new DynamicWavesScope(MODULE_DYNAMICWAVES_OSC)));


		MyBox *p_scaleFrame = manage (new MyBox("Sustain / Delay", Gtk::Orientation::ORIENTATION_HORIZONTAL));

		p_scaleFrame->pack_start(*(m_scaleSustain[i] = CreateDial("Sustain", sustain[i], NORMAL, 0.01)));
		p_scaleFrame->pack_start(*(m_scaleDelay[i] = CreateDial("Delay", attack[0][i], NORMAL, 0.01)));

		p_envPage->pack_start(*p_scaleFrame);


		MyBox *p_attackTimeFrame = manage (new MyBox("Attack Time", Gtk::Orientation::ORIENTATION_HORIZONTAL));

		p_attackTimeFrame->pack_start(*(m_scaleAttackTime1[i] = CreateDial("Time 1", attack[1][i], NORMAL, 0.01)));
		p_attackTimeFrame->pack_start(*(m_scaleAttackTime2[i] = CreateDial("Time 2", attack[3][i], NORMAL, 0.01)));
		p_attackTimeFrame->pack_start(*(m_scaleAttackTime3[i] = CreateDial("Time 3", attack[5][i], NORMAL, 0.01)));
		p_attackTimeFrame->pack_start(*(m_scaleAttackTime4[i] = CreateDial("Time 4", attack[7][i], NORMAL, 0.01)));

		p_envPage->pack_start(*p_attackTimeFrame);


		MyBox *p_attackLevelFrame = manage (new MyBox("Attack Level", Gtk::Orientation::ORIENTATION_HORIZONTAL));

		p_attackLevelFrame->pack_start(*(m_scaleAttackLevel1[i] = CreateDial("Level 1", attack[2][i], NORMAL, 0.01)));
		p_attackLevelFrame->pack_start(*(m_scaleAttackLevel2[i] = CreateDial("Level 2", attack[4][i], NORMAL, 0.01)));
		p_attackLevelFrame->pack_start(*(m_scaleAttackLevel3[i] = CreateDial("Level 3", attack[6][i], NORMAL, 0.01)));

		p_envPage->pack_start(*p_attackLevelFrame);


		MyBox *p_releaseTimeFrame = manage (new MyBox("Release Time", Gtk::Orientation::ORIENTATION_HORIZONTAL));

		p_releaseTimeFrame->pack_start(*(m_scaleReleaseTime1[i] = CreateDial("Time 1", release[0][i], NORMAL, 0.01)));
		p_releaseTimeFrame->pack_start(*(m_scaleReleaseTime2[i] = CreateDial("Time 2", release[2][i], NORMAL, 0.01)));
		p_releaseTimeFrame->pack_start(*(m_scaleReleaseTime3[i] = CreateDial("Time 3", release[4][i], NORMAL, 0.01)));

		p_envPage->pack_start(*p_releaseTimeFrame);


		MyBox *p_releaseLevelFrame = manage (new MyBox("Release Level", Gtk::Orientation::ORIENTATION_HORIZONTAL));

		p_releaseLevelFrame->pack_start(*(m_scaleReleaseLevel1[i] = CreateDial("Level 1", release[1][i], NORMAL, 0.01)));
		p_releaseLevelFrame->pack_start(*(m_scaleReleaseLevel2[i] = CreateDial("Level 2", release[3][i], NORMAL, 0.01)));

		p_envPage->pack_start(*p_releaseLevelFrame);


		p_tabs->append_page(*p_envPage, "Env " + std::to_string(i+1));
	}

	p_background->add(*p_tabs);
	add(*p_background);

	Gtk::manage(p_tabs);
}

void DynamicWavesGUI::get_waveform()
{
	for( int i = 0; i < MODULE_DYNAMICWAVES_OSC; i++ )
	{
		this->write_control(waveForm[i], m_comboWaveForm[i]->get_active_row_number());
	}
}

LabeledDial* DynamicWavesGUI::CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step)
{
	peg_data_t p_portData = p_ports[PortIndex];
	LabeledDial* p_tempDial = new LabeledDial(TextLabel, p_portData.min, p_portData.max, Type, Step);
	p_tempDial->signal_value_changed().connect(compose(bind<0>(mem_fun(*this, &DynamicWavesGUI::write_control), PortIndex), mem_fun(*p_tempDial, &LabeledDial::get_value)));

	return p_tempDial;
}

void DynamicWavesGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
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
		case p_timeScale:
			m_timescale->set_value(*static_cast<const float*> (buffer));
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

		else if ( port == attack[0][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueDelay[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleDelay[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[1][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackTime1[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackTime1[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[2][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackLevel1[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackLevel1[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[3][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackTime2[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackTime2[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[4][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackLevel2[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackLevel2[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[5][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackTime3[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackTime3[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[6][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackLevel3[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackLevel3[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if ( port == attack[7][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueAttackTime4[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleAttackTime4[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == sustain[i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueSustain[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleSustain[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == release[0][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueReleaseTime1[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleReleaseTime1[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == release[1][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueReleaseLevel1[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleReleaseLevel1[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == release[2][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueReleaseTime2[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleReleaseTime2[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == release[3][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueReleaseLevel2[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleReleaseLevel2[i]->set_value(*static_cast<const float*> (buffer));
		}
		else if( port == release[4][i] )
		{
			for( int j=0 ; j<MODULE_DYNAMICWAVES_OSC+1 ; j++)
			{
				m_envScope[j]->m_valueReleaseTime3[i] = *static_cast<const float*> (buffer);
				m_envScope[j]->Redraw();
			}
			m_scaleReleaseTime2[i]->set_value(*static_cast<const float*> (buffer));
		}
	}
}

#if OSC_COUNT == 4
	static int _ = DynamicWavesGUI::register_class("http://github.com/blablack/ams-lv2/dynamicwaves_4/gui");
#elif OSC_COUNT == 6
	static int _ = DynamicWavesGUI::register_class("http://github.com/blablack/ams-lv2/dynamicwaves_6/gui");
#elif OSC_COUNT == 8
	static int _ = DynamicWavesGUI::register_class("http://github.com/blablack/ams-lv2/dynamicwaves_8/gui");
#endif


