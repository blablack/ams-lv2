#ifndef VCTOHZ_GUI_H
#define VCTOHZ_GUI_H

class VCToHZGUI: public UI<VCToHZGUI, GtkUI<true>>
{
	public:
		VCToHZGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboConversionMode;

		LabeledDial* m_dialOctaveOffset;
};

#endif
