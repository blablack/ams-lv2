#ifndef CVS_GUI_H
#define CVS_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class CVSGUI: public UI<CVSGUI, GtkUI<true>>
{
	public:
		CVSGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
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
