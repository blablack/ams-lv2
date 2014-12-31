#ifndef MOOGLPF_GUI_H
#define MOOGLPF_GUI_H

class MoogLPFGUI: public UI<MoogLPFGUI, GtkUI<true>>
{
	public:
		MoogLPFGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialInputGain;
		LabeledDial* m_dialOutputGain;
		LabeledDial* m_dialFrequency;
		LabeledDial* m_dialExpFMGain;
		LabeledDial* m_dialResonance;
		LabeledDial* m_dialResonanceGain;
};

#endif
