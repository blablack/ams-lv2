#ifndef AMP_GUI_H
#define AMP_GUI_H

class SampleHoldGUI: public UI<SampleHoldGUI, GtkUI<true>>
{
	public:
		SampleHoldGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialTriggerLevel;
};

#endif
