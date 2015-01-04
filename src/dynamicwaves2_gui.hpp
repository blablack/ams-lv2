#ifndef DYNAMICWAVES2_GUI_H
#define DYNAMICWAVES2_GUI_H

#if OSC_COUNT == 4
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	4
#elif OSC_COUNT == 6
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	6
#elif OSC_COUNT == 8
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	8
#endif

class DynamicWaves2GUI: public UI<DynamicWaves2GUI, GtkUI<true>>
{
	public:
		DynamicWaves2GUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:

		float m_valueSustain[MODULE_DYNAMICWAVES_OSC];
		float m_valueDelay[MODULE_DYNAMICWAVES_OSC];

		float m_valueAttackTime1[MODULE_DYNAMICWAVES_OSC];
		float m_valueAttackTime2[MODULE_DYNAMICWAVES_OSC];
		float m_valueAttackTime3[MODULE_DYNAMICWAVES_OSC];
		float m_valueAttackTime4[MODULE_DYNAMICWAVES_OSC];

		float m_valueAttackLevel1[MODULE_DYNAMICWAVES_OSC];
		float m_valueAttackLevel2[MODULE_DYNAMICWAVES_OSC];
		float m_valueAttackLevel3[MODULE_DYNAMICWAVES_OSC];

		float m_valueReleaseTime1[MODULE_DYNAMICWAVES_OSC];
		float m_valueReleaseTime2[MODULE_DYNAMICWAVES_OSC];
		float m_valueReleaseTime3[MODULE_DYNAMICWAVES_OSC];

		float m_valueReleaseLevel1[MODULE_DYNAMICWAVES_OSC];
		float m_valueReleaseLevel2[MODULE_DYNAMICWAVES_OSC];

#if OSC_COUNT == 4
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune};
		p_port_enum semitone[MODULE_DYNAMICWAVES_OSC] = {p_vco1_semitone, p_vco2_semitone, p_vco3_semitone, p_vco4_semitone};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm};

		p_port_enum attack[8][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_delay, p_env2_delay, p_env3_delay, p_env4_delay},
			{p_env1_attackTime1, p_env2_attackTime1, p_env3_attackTime1, p_env4_attackTime1},
			{p_env1_attackLevel1, p_env2_attackLevel1, p_env3_attackLevel1, p_env4_attackLevel1},
			{p_env1_attackTime2, p_env2_attackTime2, p_env3_attackTime2, p_env4_attackTime2},
			{p_env1_attackLevel2, p_env2_attackLevel2, p_env3_attackLevel2, p_env4_attackLevel2},
			{p_env1_attackTime3, p_env2_attackTime3, p_env3_attackTime3, p_env4_attackTime3},
			{p_env1_attackLevel3, p_env2_attackLevel3, p_env3_attackLevel3, p_env4_attackLevel3},
			{p_env1_attackTime4, p_env2_attackTime4, p_env3_attackTime4, p_env4_attackTime4}
		};

		p_port_enum sustain[MODULE_DYNAMICWAVES_OSC] = {p_env1_sustain, p_env2_sustain, p_env3_sustain, p_env4_sustain};

		p_port_enum release[5][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_releaseTime1, p_env2_releaseTime1, p_env3_releaseTime1, p_env4_releaseTime1},
			{p_env1_releaseLevel1, p_env2_releaseLevel1, p_env3_releaseLevel1, p_env4_releaseLevel1},
			{p_env1_releaseTime2, p_env2_releaseTime2, p_env3_releaseTime2, p_env4_releaseTime2},
			{p_env1_releaseLevel2, p_env2_releaseLevel2, p_env3_releaseLevel2, p_env4_releaseLevel2},
			{p_env1_releaseTime3, p_env2_releaseTime3, p_env3_releaseTime3, p_env4_releaseTime3}
		};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4};
#elif OSC_COUNT == 6
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave, p_vco5_octave, p_vco6_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune, p_vco5_tune, p_vco6_tune};
		p_port_enum semitone[MODULE_DYNAMICWAVES_OSC] = {p_vco1_semitone, p_vco2_semitone, p_vco3_semitone, p_vco4_semitone, p_vco5_semitone, p_vco6_semitone};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0, p_vco5_phi0, p_vco6_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm, p_vco5_waveForm, p_vco6_waveForm};

		p_port_enum attack[8][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_delay, p_env2_delay, p_env3_delay, p_env4_delay, p_env5_delay, p_env6_delay},
			{p_env1_attackTime1, p_env2_attackTime1, p_env3_attackTime1, p_env4_attackTime1, p_env5_attackTime1, p_env6_attackTime1},
			{p_env1_attackLevel1, p_env2_attackLevel1, p_env3_attackLevel1, p_env4_attackLevel1, p_env5_attackLevel1, p_env6_attackLevel1},
			{p_env1_attackTime2, p_env2_attackTime2, p_env3_attackTime2, p_env4_attackTime2, p_env5_attackTime2, p_env6_attackTime2},
			{p_env1_attackLevel2, p_env2_attackLevel2, p_env3_attackLevel2, p_env4_attackLevel2, p_env5_attackLevel2, p_env6_attackLevel2},
			{p_env1_attackTime3, p_env2_attackTime3, p_env3_attackTime3, p_env4_attackTime3, p_env5_attackTime3, p_env6_attackTime3},
			{p_env1_attackLevel3, p_env2_attackLevel3, p_env3_attackLevel3, p_env4_attackLevel3, p_env5_attackLevel3, p_env6_attackLevel3},
			{p_env1_attackTime4, p_env2_attackTime4, p_env3_attackTime4, p_env4_attackTime4, p_env5_attackTime4, p_env6_attackTime4}
		};

		p_port_enum sustain[MODULE_DYNAMICWAVES_OSC] = {p_env1_sustain, p_env2_sustain, p_env3_sustain, p_env4_sustain, p_env5_sustain, p_env6_sustain};

		p_port_enum release[5][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_releaseTime1, p_env2_releaseTime1, p_env3_releaseTime1, p_env4_releaseTime1, p_env5_releaseTime1, p_env6_releaseTime1},
			{p_env1_releaseLevel1, p_env2_releaseLevel1, p_env3_releaseLevel1, p_env4_releaseLevel1, p_env5_releaseLevel1, p_env6_releaseLevel1},
			{p_env1_releaseTime2, p_env2_releaseTime2, p_env3_releaseTime2, p_env4_releaseTime2, p_env5_releaseTime2, p_env6_releaseTime2},
			{p_env1_releaseLevel2, p_env2_releaseLevel2, p_env3_releaseLevel2, p_env4_releaseLevel2, p_env5_releaseLevel2, p_env6_releaseLevel2},
			{p_env1_releaseTime3, p_env2_releaseTime3, p_env3_releaseTime3, p_env4_releaseTime3, p_env5_releaseTime3, p_env6_releaseTime3}
		};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4, p_volume5, p_volume6};
#elif OSC_COUNT == 8
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave, p_vco5_octave, p_vco6_octave, p_vco7_octave, p_vco8_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune, p_vco5_tune, p_vco6_tune, p_vco7_tune, p_vco8_tune};
		p_port_enum semitone[MODULE_DYNAMICWAVES_OSC] = {p_vco1_semitone, p_vco2_semitone, p_vco3_semitone, p_vco4_semitone, p_vco5_semitone, p_vco6_semitone, p_vco7_semitone, p_vco8_semitone};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0, p_vco5_phi0, p_vco6_phi0, p_vco7_phi0, p_vco8_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm, p_vco5_waveForm, p_vco6_waveForm, p_vco7_waveForm, p_vco8_waveForm};

		p_port_enum attack[8][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_delay, p_env2_delay, p_env3_delay, p_env4_delay, p_env5_delay, p_env6_delay, p_env7_delay, p_env8_delay},
			{p_env1_attackTime1, p_env2_attackTime1, p_env3_attackTime1, p_env4_attackTime1, p_env5_attackTime1, p_env6_attackTime1, p_env7_attackTime1, p_env8_attackTime1},
			{p_env1_attackLevel1, p_env2_attackLevel1, p_env3_attackLevel1, p_env4_attackLevel1, p_env5_attackLevel1, p_env6_attackLevel1, p_env7_attackLevel1, p_env8_attackLevel1},
			{p_env1_attackTime2, p_env2_attackTime2, p_env3_attackTime2, p_env4_attackTime2, p_env5_attackTime2, p_env6_attackTime2, p_env7_attackTime2, p_env8_attackTime2},
			{p_env1_attackLevel2, p_env2_attackLevel2, p_env3_attackLevel2, p_env4_attackLevel2, p_env5_attackLevel2, p_env6_attackLevel2, p_env7_attackLevel2, p_env8_attackLevel2},
			{p_env1_attackTime3, p_env2_attackTime3, p_env3_attackTime3, p_env4_attackTime3, p_env5_attackTime3, p_env6_attackTime3, p_env7_attackTime3, p_env8_attackTime3},
			{p_env1_attackLevel3, p_env2_attackLevel3, p_env3_attackLevel3, p_env4_attackLevel3, p_env5_attackLevel3, p_env6_attackLevel3, p_env7_attackLevel3, p_env8_attackLevel3},
			{p_env1_attackTime4, p_env2_attackTime4, p_env3_attackTime4, p_env4_attackTime4, p_env5_attackTime4, p_env6_attackTime4, p_env7_attackTime4, p_env8_attackTime4}
		};

		p_port_enum sustain[MODULE_DYNAMICWAVES_OSC] = {p_env1_sustain, p_env2_sustain, p_env3_sustain, p_env4_sustain, p_env5_sustain, p_env6_sustain, p_env7_sustain, p_env8_sustain};

		p_port_enum release[5][MODULE_DYNAMICWAVES_OSC] =
		{
			{p_env1_releaseTime1, p_env2_releaseTime1, p_env3_releaseTime1, p_env4_releaseTime1, p_env5_releaseTime1, p_env6_releaseTime1, p_env7_releaseTime1, p_env8_releaseTime1},
			{p_env1_releaseLevel1, p_env2_releaseLevel1, p_env3_releaseLevel1, p_env4_releaseLevel1, p_env5_releaseLevel1, p_env6_releaseLevel1, p_env7_releaseLevel1, p_env8_releaseLevel1},
			{p_env1_releaseTime2, p_env2_releaseTime2, p_env3_releaseTime2, p_env4_releaseTime2, p_env5_releaseTime2, p_env6_releaseTime2, p_env7_releaseTime2, p_env8_releaseTime2},
			{p_env1_releaseLevel2, p_env2_releaseLevel2, p_env3_releaseLevel2, p_env4_releaseLevel2, p_env5_releaseLevel2, p_env6_releaseLevel2, p_env7_releaseLevel2, p_env8_releaseLevel2},
			{p_env1_releaseTime3, p_env2_releaseTime3, p_env3_releaseTime3, p_env4_releaseTime3, p_env5_releaseTime3, p_env6_releaseTime3, p_env7_releaseTime3, p_env8_releaseTime3}
		};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4, p_volume5, p_volume6, p_volume7, p_volume8};
#endif

		DynamicWavesScope* m_envScope[MODULE_DYNAMICWAVES_OSC+1];

		// MAIN //
		LabeledDial* m_octave;
		LabeledDial* m_tune;

		LabeledDial* m_expFMGain;
		LabeledDial* m_linFMGain;

		LabeledDial* m_timescale;

		LabeledDial* m_mixer[MODULE_DYNAMICWAVES_OSC];

		// OSC //

		Gtk::ComboBoxText* m_comboWaveForm[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleOctave[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleTune[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleSemitone[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scalePhi0[MODULE_DYNAMICWAVES_OSC];

		// ENV //

		LabeledDial* m_scaleSustain[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleDelay[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleAttackTime1[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleAttackTime2[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleAttackTime3[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleAttackTime4[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleAttackLevel1[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleAttackLevel2[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleAttackLevel3[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleReleaseTime1[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleReleaseTime2[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleReleaseTime3[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleReleaseLevel1[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleReleaseLevel2[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
		void get_waveform();

};

#endif
