#ifndef VCDELAY_GUI_H
#define VCDELAY_GUI_H

class VCDelayGUI: public UI<VCDelayGUI, GtkUI<true>>
{
	public:
		VCDelayGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialDelay;
		LabeledDial* m_dialVMod;
};

#endif
