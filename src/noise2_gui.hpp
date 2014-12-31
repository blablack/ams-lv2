#ifndef NOISE2_GUI_H
#define NOISE2_GUI_H

class Noise2GUI: public UI<Noise2GUI, GtkUI<true>>
{
	public:
		Noise2GUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboNoiseForm;
		LabeledDial* m_dialRandomRate;
		LabeledDial* m_dialRandomLevel;

		void get_waveform();
		void deactive_gui_parts();
};

#endif
