#ifndef MIXER_4CH_GUI_H
#define MIXER_4CH_GUI_H

class Mixer4ChGUI: public UI<Mixer4ChGUI, GtkUI<true>>
{
	public:
		Mixer4ChGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialGain;
		LabeledDial* m_dialVolume1;
		LabeledDial* m_dialVolume2;
		LabeledDial* m_dialVolume3;
		LabeledDial* m_dialVolume4;
};

#endif
