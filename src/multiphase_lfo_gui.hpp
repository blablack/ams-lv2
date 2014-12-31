#ifndef MULTIPHASE_LFO_GUI_H
#define MULTIPHASE_LFO_GUI_H

class MultiphaseLfoGUI: public UI<MultiphaseLfoGUI, GtkUI<true>>
{
	public:
		MultiphaseLfoGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialFreq;
		LabeledDial* m_dialGainSaw;
		LabeledDial* m_dialGainTri;

		Gtk::ComboBoxText* m_comboSawMode;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
};

#endif
