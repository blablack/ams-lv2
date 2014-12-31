#ifndef VCORGAN_GUI_H
#define VCORGAN_GUI_H

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

class VCOrganGUI: public UI<VCOrganGUI, GtkUI<true>>
{
	public:
		VCOrganGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
#if OSC_COUNT == 4
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune};
		p_port_enum harmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_harmonic, p_vco2_harmonic, p_vco3_harmonic, p_vco4_harmonic};
		p_port_enum subharmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_subharmonic, p_vco2_subharmonic, p_vco3_subharmonic, p_vco4_subharmonic};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4};
#elif OSC_COUNT == 6
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave, p_vco5_octave, p_vco6_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune, p_vco5_tune, p_vco6_tune};
		p_port_enum harmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_harmonic, p_vco2_harmonic, p_vco3_harmonic, p_vco4_harmonic, p_vco5_harmonic, p_vco6_harmonic};
		p_port_enum subharmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_subharmonic, p_vco2_subharmonic, p_vco3_subharmonic, p_vco4_subharmonic, p_vco5_subharmonic, p_vco6_subharmonic};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0, p_vco5_phi0, p_vco6_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm, p_vco5_waveForm, p_vco6_waveForm};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4, p_volume5, p_volume6};
#elif OSC_COUNT == 8
		p_port_enum osc_octave[MODULE_DYNAMICWAVES_OSC] = {p_vco1_octave, p_vco2_octave, p_vco3_octave, p_vco4_octave, p_vco5_octave, p_vco6_octave, p_vco7_octave, p_vco8_octave};
		p_port_enum osc_tune[MODULE_DYNAMICWAVES_OSC] = {p_vco1_tune, p_vco2_tune, p_vco3_tune, p_vco4_tune, p_vco5_tune, p_vco6_tune, p_vco7_tune, p_vco8_tune};
		p_port_enum harmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_harmonic, p_vco2_harmonic, p_vco3_harmonic, p_vco4_harmonic, p_vco5_harmonic, p_vco6_harmonic, p_vco7_harmonic, p_vco8_harmonic};
		p_port_enum subharmonic[MODULE_DYNAMICWAVES_OSC] = {p_vco1_subharmonic, p_vco2_subharmonic, p_vco3_subharmonic, p_vco4_subharmonic, p_vco5_subharmonic, p_vco6_subharmonic, p_vco7_subharmonic, p_vco8_subharmonic};
		p_port_enum phi0[MODULE_DYNAMICWAVES_OSC] = {p_vco1_phi0, p_vco2_phi0, p_vco3_phi0, p_vco4_phi0, p_vco5_phi0, p_vco6_phi0, p_vco7_phi0, p_vco8_phi0};
		p_port_enum waveForm[MODULE_DYNAMICWAVES_OSC] = {p_vco1_waveForm, p_vco2_waveForm, p_vco3_waveForm, p_vco4_waveForm, p_vco5_waveForm, p_vco6_waveForm, p_vco7_waveForm, p_vco8_waveForm};

		p_port_enum volume[MODULE_DYNAMICWAVES_OSC] = {p_volume1, p_volume2, p_volume3, p_volume4, p_volume5, p_volume6, p_volume7, p_volume8};
#endif

		// MAIN //
		LabeledDial* m_octave;
		LabeledDial* m_tune;

		LabeledDial* m_expFMGain;
		LabeledDial* m_linFMGain;

		LabeledDial* m_mixer[MODULE_DYNAMICWAVES_OSC];

		// OSC //
		Gtk::ComboBoxText* m_comboWaveForm[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scaleOctave[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleTune[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleHarmonic[MODULE_DYNAMICWAVES_OSC];
		LabeledDial* m_scaleSubharmonic[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* m_scalePhi0[MODULE_DYNAMICWAVES_OSC];

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
		void get_waveform();

};

#endif
