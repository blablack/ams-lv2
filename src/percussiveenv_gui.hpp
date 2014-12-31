#ifndef ENV_GUI_H
#define ENV_GUI_H

class PercussiveEnvGUI: public UI<PercussiveEnvGUI, GtkUI<true>>
{
	public:
		PercussiveEnvGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		float m_attackValue, m_decayValue, m_delayValue, m_holdValue;
		PercussiveEnvGUIScope* m_envScope;

		LabeledDial* m_scaleAttack;
		LabeledDial* m_scaleDecay;
		LabeledDial* m_scaleDelay;
		LabeledDial* m_scaleHold;
		LabeledDial* m_scaleTimeScale;
};

#endif
