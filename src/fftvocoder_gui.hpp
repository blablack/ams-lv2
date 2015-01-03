#ifndef FFTVOCODER_GUI_H
#define FFTVOCODER_GUI_H

class FFTVocoderGUI: public UI<FFTVocoderGUI, GtkUI<true>>
{
	public:
		FFTVocoderGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_scaleBinsChannel;
		LabeledDial* m_scaleVCBinsChannels;
		LabeledDial* m_scaleAttackTime;
		LabeledDial* m_scaleReleaseTime;
		LabeledDial* m_scalePitchShiftOctave;
		LabeledDial* m_scaleVCPitchShift;
		LabeledDial* m_scaleFrequencyBodeShift;
		LabeledDial* m_scaleVCFreqShift;
		LabeledDial* m_scalePhaseShift;

		Gtk::ComboBoxText* m_comboFFTWindowFunction;

		Gtk::CheckButton* m_checkDynamicSlicing;
		Gtk::CheckButton* m_RThetaModulaotr;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
		Gtk::CheckButton* CreateCheck(const std::string TextLabel, int PortNum);
};

#endif
