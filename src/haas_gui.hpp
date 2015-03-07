#ifndef HAAS_GUI_H
#define HAAS_GUI_H

class HaasGUI: public UI<HaasGUI, GtkUI<true>>
{
	public:
		HaasGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialDelay;
		LabeledDial* m_dialMix;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
};

#endif
