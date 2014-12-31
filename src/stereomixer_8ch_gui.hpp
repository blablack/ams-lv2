#ifndef STEREOMIXER_8CH_GUI_H
#define STEREOMIXER_8CH_GUI_H

class StereoMixer8ChGUI: public UI<StereoMixer8ChGUI, GtkUI<true>>
{
	public:
		StereoMixer8ChGUI(const std::string& URI);
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

		CheckButton* m_checkMute5;
		CheckButton* m_checkSolo5;
		LabeledDial* m_dialVolume5;
		LabeledDial* m_dialPan5;

		CheckButton* m_checkMute6;
		CheckButton* m_checkSolo6;
		LabeledDial* m_dialVolume6;
		LabeledDial* m_dialPan6;

		CheckButton* m_checkMute7;
		CheckButton* m_checkSolo7;
		LabeledDial* m_dialVolume7;
		LabeledDial* m_dialPan7;

		CheckButton* m_checkMute8;
		CheckButton* m_checkSolo8;
		LabeledDial* m_dialVolume8;
		LabeledDial* m_dialPan8;

		LabeledDial* CreateDial(const std::string TextLabel, double Value, double Min, double Max, DialType Type, double Step);
		CheckButton* CreateCheck(const std::string TextLabel, int PortNum);
};

#endif
