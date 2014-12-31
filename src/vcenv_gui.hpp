#ifndef VCENV_GUI_H
#define VCENV_GUI_H

class VCEnvGUI: public UI<VCEnvGUI, GtkUI<true>>
{
	public:
		VCEnvGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialAttackOffset;
		LabeledDial* m_dialDecayOffset;
		LabeledDial* m_dialSustainOffset;
		LabeledDial* m_dialReleaseOffset;

		LabeledDial* m_dialAttackGain;
		LabeledDial* m_dialDecayGain;
		LabeledDial* m_dialSustainGain;
		LabeledDial* m_dialReleaseGain;

		Gtk::ComboBoxText* m_comboTimescale;
		Gtk::ComboBoxText* m_comboDecayReleaseMode;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
};

#endif
