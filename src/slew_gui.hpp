#ifndef SLEW_GUI_H
#define SLEW_GUI_H

class SlewGUI: public UI<SlewGUI, GtkUI<true>>
{
	public:
		SlewGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialTimeUp;
		LabeledDial* m_dialTimeDown;
};

#endif
