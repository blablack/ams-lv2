#ifndef LFO_GUI_H
#define LFO_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class LfoGUI: public UI<LfoGUI, GtkUI<true>>
{
	public:
		LfoGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialTempo;
		LabeledDial* m_dialPhi0;
};

#endif
