#ifndef MIXER_4CH_CV_GUI_H
#define MIXER_4CH_CV_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class Mixer4ChCVGUI: public UI<Mixer4ChCVGUI, GtkUI<true>>
{
	public:
		Mixer4ChCVGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialGain;
		LabeledDial* m_dialVolume1;
		LabeledDial* m_dialVolume2;
		LabeledDial* m_dialVolume3;
		LabeledDial* m_dialVolume4;

		float get_gain();
		float get_volume1();
		float get_volume2();
		float get_volume3();
		float get_volume4();
};

#endif
