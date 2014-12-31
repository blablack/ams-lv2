#ifndef RINGMODULATOR_GUI_H
#define RINGMODULATOR_GUI_H

class RingModulatorGUI: public UI<RingModulatorGUI, GtkUI<true>>
{
	public:
		RingModulatorGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain;
};

#endif
