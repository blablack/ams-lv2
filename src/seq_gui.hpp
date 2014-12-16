#ifndef ENV_GUI_H
#define ENV_GUI_H

class SeqGUI: public UI<SeqGUI, GtkUI<true>>
{
	public:
		SeqGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);
};

#endif
