#ifndef AD_GUI_H
#define AD_GUI_H

class AdGUI: public UI<AdGUI, GtkUI<true>>
{
	public:
		AdGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialDetuneAmplitude;
		LabeledDial* m_dialDetuneModulation;
		LabeledDial* m_dialDetuneRate;
		LabeledDial* m_dialDriftAmplitude;
		LabeledDial* m_dialDriftModulation;
		LabeledDial* m_dialDriftRate;
};

#endif
