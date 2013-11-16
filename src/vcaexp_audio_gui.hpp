#ifndef VCAEXP_AUDIO_GUI_H
#define VCAEXP_AUDIO_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class VCAExpAudioGUI: public UI<VCAExpAudioGUI, GtkUI<true>>
{
	public:
		VCAExpAudioGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialGain1;
		LabeledDial* m_dialGain2;
		LabeledDial* m_dialIn1;
		LabeledDial* m_dialIn2;
		LabeledDial* m_dialOutputLevel;


		float get_gain1();
		float get_gain2();
		float get_in1();
		float get_in2();
		float get_outputLevel();
};

#endif
