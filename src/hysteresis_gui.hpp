#ifndef HYSTERESIS_GUI_H
#define HYSTERESIS_GUI_H

class HysteresisGUI: public UI<HysteresisGUI, GtkUI<true>>
{
	public:
		HysteresisGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialCenter;
		LabeledDial* m_dialOverlap;
		LabeledDial* m_dialLowSlope;
		//LabeledDial* m_dialLowOffset;
		LabeledDial* m_dialHighSlope;
		//LabeledDial* m_dialHighOffset;

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
};

#endif
