#ifndef VCAEXP_GUI_H
#define VCAEXP_GUI_H

class VcaExpGUI: public UI<VcaExpGUI, GtkUI<true>>
{
	public:
		VcaExpGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain1;
		LabeledDial* m_dialGain2;
		LabeledDial* m_dialIn1;
		LabeledDial* m_dialIn2;
		LabeledDial* m_dialOutputLevel;
};

#endif
