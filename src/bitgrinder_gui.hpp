#ifndef BITGRINDER_GUI_H
#define BITGRINDER_GUI_H

class BitGrinderGUI: public UI<BitGrinderGUI, GtkUI<true>>
{
	public:
		BitGrinderGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialFractionalDataRate;
		LabeledDial* m_dialRateVCModulation;
		LabeledDial* m_dialBitsPerVolt;
		LabeledDial* m_dialBitsVCModulation;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
};

#endif
