#ifndef STEREOMIXER_4CH_GUI_H
#define STEREOMIXER_4CH_GUI_H

class StereoMixer4ChGUI: public UI<StereoMixer4ChGUI, GtkUI<true>>
{
	public:
		StereoMixer4ChGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialMasterVolume;

		CheckButton* m_checkMute1;
		CheckButton* m_checkSolo1;
		LabeledDial* m_dialVolume1;
		LabeledDial* m_dialPan1;

		CheckButton* m_checkMute2;
		CheckButton* m_checkSolo2;
		LabeledDial* m_dialVolume2;
		LabeledDial* m_dialPan2;

		CheckButton* m_checkMute3;
		CheckButton* m_checkSolo3;
		LabeledDial* m_dialVolume3;
		LabeledDial* m_dialPan3;

		CheckButton* m_checkMute4;
		CheckButton* m_checkSolo4;
		LabeledDial* m_dialVolume4;
		LabeledDial* m_dialPan4;

		LabeledDial* CreateDial(const std::string TextLabel, double Value, double Min, double Max, DialType Type, double Step);
		CheckButton* CreateCheck(const std::string TextLabel, int PortNum);
};

#endif
