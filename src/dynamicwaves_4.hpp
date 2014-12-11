#ifndef DYNAMICWAVES_4_H
#define DYNAMICWAVES_4_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"
#include "dynamicwaves_4_ttl.hpp"

#define MODULE_DYNAMICWAVES_OSC				4
#define DYNAMICWAVES_ENVELOPE_RESPONSE		256

using namespace lvtk;

enum dynamicWaveFormType
{
	DYNAMICWAVE_SINE,
	DYNAMICWAVE_SAW,
	DYNAMICWAVE_TRI,
	DYNAMICWAVE_RECT,
	DYNAMICWAVE_SAW2
};

class DynamicWaves4: public Plugin<DynamicWaves4>
{
	private:
		double m_rate;
		float wave_period, wave_period_2;
		bool allEnvTerminated, noteActive, gate, retrigger;

		bool oscActive[MODULE_DYNAMICWAVES_OSC];
		float e[MODULE_DYNAMICWAVES_OSC];
		long noteOnOfs[MODULE_DYNAMICWAVES_OSC], noteOffOfs[MODULE_DYNAMICWAVES_OSC];
		float e_noteOff[MODULE_DYNAMICWAVES_OSC], de[MODULE_DYNAMICWAVES_OSC], de_release[MODULE_DYNAMICWAVES_OSC];
		float phi[MODULE_DYNAMICWAVES_OSC];

		float *gateData;
		float *retriggerData;
		float *freqData;
		float *expFMData;
		float *linFMData;

		SynthData *synthdata;

	public:
		DynamicWaves4(double rate);
		void run(uint32_t nframes);
};

#endif
