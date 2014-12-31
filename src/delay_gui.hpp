#ifndef DELAY_GUI_H
#define DELAY_GUI_H

class DelayGUI: public UI<DelayGUI, GtkUI<true>>
{
	public:
		DelayGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialDelay;
};

#endif
