#ifndef AMP_GUI_H
#define AMP_GUI_H

class AmpGUI: public UI<AmpGUI, GtkUI<true>>
{
	public:
		AmpGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain;
};

#endif
