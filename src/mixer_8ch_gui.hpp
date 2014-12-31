#ifndef MIXER_8CH_GUI_H
#define MIXER_8CH_GUI_H

class Mixer8ChGUI: public UI<Mixer8ChGUI, GtkUI<true>>
{
	public:
		Mixer8ChGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain;
		LabeledDial* m_dialVolume1;
		LabeledDial* m_dialVolume2;
		LabeledDial* m_dialVolume3;
		LabeledDial* m_dialVolume4;
		LabeledDial* m_dialVolume5;
		LabeledDial* m_dialVolume6;
		LabeledDial* m_dialVolume7;
		LabeledDial* m_dialVolume8;
};

#endif
