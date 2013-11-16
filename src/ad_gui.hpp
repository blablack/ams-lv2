#ifndef AD_GUI_H
#define AD_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class AdGUI: public UI<AdGUI, GtkUI<true>>
{
	public:
		AdGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialDetuneAmplitude;
		LabeledDial* m_dialDetuneModulation;
		LabeledDial* m_dialDetuneRate;
		LabeledDial* m_dialDriftAmplitude;
		LabeledDial* m_dialDriftModulation;
		LabeledDial* m_dialDriftRate;

		float get_detuneAmplitude();
		float get_detuneModulation();
		float get_detuneRate();
		float get_driftAmplitude();
		float get_driftModulation();
		float get_driftRate();
};

#endif
