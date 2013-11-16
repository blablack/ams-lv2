#ifndef MOOGLPF_GUI_H
#define MOOGLPF_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class MoogLPFGUI: public UI<MoogLPFGUI, GtkUI<true>>
{
	public:
		MoogLPFGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		LabeledDial* m_dialInputGain;
		LabeledDial* m_dialOutputGain;
		LabeledDial* m_dialFrequency;
		LabeledDial* m_dialExpFMGain;
		LabeledDial* m_dialResonance;
		LabeledDial* m_dialResonanceGain;

		float get_inputGain();
		float get_outputGain();
		float get_frequency();
		float get_expFMGain();
		float get_resonance();
		float get_resonanceGain();
};

#endif
