#ifndef LFO2_FREQ_GUI_H
#define LFO2_FREQ_GUI_H

class Lfo2FreqGUI: public UI<Lfo2FreqGUI, GtkUI<true>>
{
	public:
		Lfo2FreqGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboWaveForm;
		LabeledDial* m_dialTempo;
		LabeledDial* m_dialPhi0;
};

#endif
