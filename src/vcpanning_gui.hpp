#ifndef VCPANNING_GUI_H
#define VCPANNING_GUI_H

class VcPanningGUI: public UI<VcPanningGUI, GtkUI<true>>
{
	public:
		VcPanningGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		Gtk::ComboBoxText* m_comboPanningMode;

		LabeledDial* m_scalePanOffset;
		LabeledDial* m_scalePanGain;
};

#endif
