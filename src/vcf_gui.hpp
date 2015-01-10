#ifndef VCF_GUI_H
#define VCF_GUI_H

class VcfGUI: public UI<VcfGUI, GtkUI<true>>
{
	public:
		VcfGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboVCFType;

		LabeledDial* m_scaleInputGain;
		LabeledDial* m_scaleFrequency;
		LabeledDial* m_scaleExpFMGain;
		LabeledDial* m_scaleLinFMGain;
		LabeledDial* m_scaleResonance;
		LabeledDial* m_scaleResonanceGain;
};

#endif
