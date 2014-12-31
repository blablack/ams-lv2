#ifndef LFO2_TEMPO_GUI_H
#define LFO2_TEMPO_GUI_H

class Lfo2TempoGUI: public UI<Lfo2TempoGUI, GtkUI<true>>
{
	public:
		Lfo2TempoGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboWaveForm;
		LabeledDial* m_dialTempo;
		LabeledDial* m_dialTempoMultiplier;
		LabeledDial* m_dialPhi0;
};

#endif
