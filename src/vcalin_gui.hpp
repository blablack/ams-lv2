#ifndef VCALIN_GUI_H
#define VCALIN_GUI_H

class VcaLinGUI: public UI<VcaLinGUI, GtkUI<true>>
{
	public:
		VcaLinGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain1;
		LabeledDial* m_dialGain2;
		LabeledDial* m_dialIn1;
		LabeledDial* m_dialIn2;
		LabeledDial* m_dialOutputLevel;
};

#endif
