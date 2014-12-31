#ifndef VCSWITCH_GUI_H
#define VCSWITCH_GUI_H

class VCSwitchGUI: public UI<VCSwitchGUI, GtkUI<true>>
{
	public:
		VCSwitchGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialSwitchLevel;
};

#endif
