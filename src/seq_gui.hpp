#ifndef ENV_GUI_H
#define ENV_GUI_H

#if STEP_COUNT == 8
#undef MODULE_STEP_COUNT
#define MODULE_STEP_COUNT 8
#elif STEP_COUNT == 12
#undef MODULE_STEP_COUNT
#define MODULE_STEP_COUNT 12
#elif STEP_COUNT == 16
#undef MODULE_STEP_COUNT
#define MODULE_STEP_COUNT 16
#elif STEP_COUNT == 24
#undef MODULE_STEP_COUNT
#define MODULE_STEP_COUNT 24
#elif STEP_COUNT == 32
#undef MODULE_STEP_COUNT
#define MODULE_STEP_COUNT 32
#endif

class SeqGUI: public UI<SeqGUI, GtkUI<true>>
{
	public:
		SeqGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
#if STEP_COUNT == 8
		p_port_enum index_pitches[MODULE_STEP_COUNT] = {p_pitch1, p_pitch2, p_pitch3, p_pitch4, p_pitch5, p_pitch6, p_pitch7, p_pitch8};
		p_port_enum index_gates[MODULE_STEP_COUNT] = {p_gate1, p_gate2, p_gate3, p_gate4, p_gate5, p_gate6, p_gate7, p_gate8};
		p_port_enum index_velocities[MODULE_STEP_COUNT] = {p_velocity1, p_velocity2, p_velocity3, p_velocity4, p_velocity5, p_velocity6, p_velocity7, p_velocity8};
#elif STEP_COUNT == 12
		p_port_enum index_pitches[MODULE_STEP_COUNT] = {p_pitch1, p_pitch2, p_pitch3, p_pitch4, p_pitch5, p_pitch6, p_pitch7, p_pitch8, p_pitch9, p_pitch10, p_pitch11, p_pitch12};
		p_port_enum index_gates[MODULE_STEP_COUNT] = {p_gate1, p_gate2, p_gate3, p_gate4, p_gate5, p_gate6, p_gate7, p_gate8, p_gate9, p_gate10, p_gate11, p_gate12};
		p_port_enum index_velocities[MODULE_STEP_COUNT] = {p_velocity1, p_velocity2, p_velocity3, p_velocity4, p_velocity5, p_velocity6, p_velocity7, p_velocity8, p_velocity9, p_velocity10, p_velocity11, p_velocity12};
#elif STEP_COUNT == 16
		p_port_enum index_pitches[MODULE_STEP_COUNT] = {p_pitch1, p_pitch2, p_pitch3, p_pitch4, p_pitch5, p_pitch6, p_pitch7, p_pitch8, p_pitch9, p_pitch10, p_pitch11, p_pitch12, p_pitch13, p_pitch14, p_pitch15, p_pitch16};
		p_port_enum index_gates[MODULE_STEP_COUNT] = {p_gate1, p_gate2, p_gate3, p_gate4, p_gate5, p_gate6, p_gate7, p_gate8, p_gate9, p_gate10, p_gate11, p_gate12, p_gate13, p_gate14, p_gate15, p_gate16};
		p_port_enum index_velocities[MODULE_STEP_COUNT] = {p_velocity1, p_velocity2, p_velocity3, p_velocity4, p_velocity5, p_velocity6, p_velocity7, p_velocity8, p_velocity9, p_velocity10, p_velocity11, p_velocity12, p_velocity13, p_velocity14, p_velocity15, p_velocity16};
#elif STEP_COUNT == 24
		p_port_enum index_pitches[MODULE_STEP_COUNT] = {p_pitch1, p_pitch2, p_pitch3, p_pitch4, p_pitch5, p_pitch6, p_pitch7, p_pitch8, p_pitch9, p_pitch10, p_pitch11, p_pitch12, p_pitch13, p_pitch14, p_pitch15, p_pitch16, p_pitch17, p_pitch18, p_pitch19, p_pitch20, p_pitch21, p_pitch22, p_pitch23, p_pitch24};
		p_port_enum index_gates[MODULE_STEP_COUNT] = {p_gate1, p_gate2, p_gate3, p_gate4, p_gate5, p_gate6, p_gate7, p_gate8, p_gate9, p_gate10, p_gate11, p_gate12, p_gate13, p_gate14, p_gate15, p_gate16, p_gate17, p_gate18, p_gate19, p_gate20, p_gate21, p_gate22, p_gate24};
		p_port_enum index_velocities[MODULE_STEP_COUNT] = {p_velocity1, p_velocity2, p_velocity3, p_velocity4, p_velocity5, p_velocity6, p_velocity7, p_velocity8, p_velocity9, p_velocity10, p_velocity11, p_velocity12, p_velocity13, p_velocity14, p_velocity15, p_velocity16, p_velocity17, p_velocity18, p_velocity19, p_velocity20, p_velocity21, p_velocity22, p_velocity23, p_velocity24};
#elif STEP_COUNT == 32
		p_port_enum index_pitches[MODULE_STEP_COUNT] = {p_pitch1, p_pitch2, p_pitch3, p_pitch4, p_pitch5, p_pitch6, p_pitch7, p_pitch8, p_pitch9, p_pitch10, p_pitch11, p_pitch12, p_pitch13, p_pitch14, p_pitch15, p_pitch16, p_pitch17, p_pitch18, p_pitch19, p_pitch20, p_pitch21, p_pitch22, p_pitch23, p_pitch24, p_pitch25, p_pitch26, p_pitch27, p_pitch28, p_pitch29, p_pitch30, p_pitch31, p_pitch32};
		p_port_enum index_gates[MODULE_STEP_COUNT] = {p_gate1, p_gate2, p_gate3, p_gate4, p_gate5, p_gate6, p_gate7, p_gate8, p_gate9, p_gate10, p_gate11, p_gate12, p_gate13, p_gate14, p_gate15, p_gate16, p_gate17, p_gate18, p_gate19, p_gate20, p_gate21, p_gate22, p_gate24, p_gate25, p_gate26, p_gate27, p_gate28, p_gate29, p_gate30, p_gate31, p_gate32};
		p_port_enum index_velocities[MODULE_STEP_COUNT] = {p_velocity1, p_velocity2, p_velocity3, p_velocity4, p_velocity5, p_velocity6, p_velocity7, p_velocity8, p_velocity9, p_velocity10, p_velocity11, p_velocity12, p_velocity13, p_velocity14, p_velocity15, p_velocity16, p_velocity17, p_velocity18, p_velocity19, p_velocity20, p_velocity21, p_velocity22, p_velocity23, p_velocity24, p_velocity25, p_velocity26, p_velocity27, p_velocity28, p_velocity29, p_velocity30, p_velocity31, p_velocity32};
#endif

		LabeledDial* m_pitchOffset;
		LabeledDial* m_bpm;
		ComboBoxText* m_comboGateTime;

		LabeledDial* m_pitches[MODULE_STEP_COUNT];
		CheckButton* m_gates[MODULE_STEP_COUNT];
		LabeledDial* m_velocities[MODULE_STEP_COUNT];

		LabeledDial* CreateDial(const std::string TextLabel, p_port_enum PortIndex, DialType Type, double Step);
		CheckButton* CreateCheck(const std::string TextLabel, int PortNum);
		void get_waveform();
};

#endif
