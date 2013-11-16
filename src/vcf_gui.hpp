#ifndef VCF_GUI_H
#define VCF_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class VcfGUI: public UI<VcfGUI, GtkUI<true>>
{
public:
	VcfGUI(const std::string& URI);
	void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

protected:
	Gtk::ComboBoxText* m_comboVCFType;

	LabeledDial* m_scaleInputGain;
	LabeledDial* m_scaleFrequency;
	LabeledDial* m_scaleExpFMGain;
	LabeledDial* m_scaleLinFMGain;
	LabeledDial* m_scaleResonance;
	LabeledDial* m_scaleResonanceGain;

	float get_inputGain();
	float get_frequency();
	float get_expFMGain();
	float get_linFMGain();
	float get_resonance();
	float get_resonanceGain();
};

#endif
