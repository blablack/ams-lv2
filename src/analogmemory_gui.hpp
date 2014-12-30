#ifndef ANALOGMEMORY_GUI_H
#define ANALOGMEMORY_GUI_H

class AnalogMemoryGUI: public UI<AnalogMemoryGUI, GtkUI<true>>
{
	public:
		AnalogMemoryGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);

		Gtk::ComboBoxText* m_comboWriteAddressForm;
		LabeledDial* m_dialN;
		LabeledDial* m_dialWriteThresh;
};

#endif
