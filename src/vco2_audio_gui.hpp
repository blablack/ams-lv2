#ifndef VCO2_AUDIO_GUI_H
#define VCO2_AUDIO_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class Vco2AudioGUI: public UI<Vco2AudioGUI, GtkUI<true>>
{
public:
	Vco2AudioGUI(const char* plugin_uri);
	void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

protected:
	Gtk::ComboBoxText* m_comboWaveForm;

	LabeledDial* m_scaleOctave;
	LabeledDial* m_scaleTune;
	LabeledDial* m_scaleSemitone;
	LabeledDial* m_scalePW;
	LabeledDial* m_scalePWGain;
	LabeledDial* m_scaleEdge;
	LabeledDial* m_scalePhi0;
	LabeledDial* m_scaleExpFMGain;
	LabeledDial* m_scaleLinFMGain;

	int get_waveform();
	float get_octave();
	float get_tune();
	float get_semitone();
	float get_pw();
	float get_pwGain();
	float get_edge();
	float get_phi0();
	float get_expFMGain();
	float get_linFMGain();
};

#endif
