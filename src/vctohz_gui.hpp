#ifndef VCTOHZ_GUI_H
#define VCTOHZ_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class VCToHZGUI: public UI<VCToHZGUI, GtkUI<true>>
{
	public:
		VCToHZGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		Gtk::ComboBoxText* m_comboConversionMode;

		LabeledDial* m_dialOctaveOffset;

		float get_octaveOffset();
};

#endif
