#ifndef HZTOVCGUI_GUI_H
#define HZTOVCGUI_GUI_H

class HzToVCGUI: public UI<HzToVCGUI, GtkUI<true>>
{
	public:
		HzToVCGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialOctaveOffset;
};

#endif
