#ifndef CVS_GUI_H
#define CVS_GUI_H

class CVSGUI: public UI<CVSGUI, GtkUI<true>>
{
	public:
		CVSGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		LabeledDial* m_dialCV1;
		LabeledDial* m_dialCVFine1;
		LabeledDial* m_dialCV2;
		LabeledDial* m_dialCVFine2;
		LabeledDial* m_dialCV3;
		LabeledDial* m_dialCVFine3;
		LabeledDial* m_dialCV4;
		LabeledDial* m_dialCVFine4;
};

#endif
