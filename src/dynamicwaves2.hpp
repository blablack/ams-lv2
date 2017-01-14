#ifndef DYNAMICWAVES2_H
#define DYNAMICWAVES2_H

#include "synthdata.hpp"

#if OSC_COUNT == 4
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	4
#elif OSC_COUNT == 6
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	6
#elif OSC_COUNT == 8
#undef MODULE_DYNAMICWAVES_OSC
#define MODULE_DYNAMICWAVES_OSC	8
#endif

using namespace lvtk;

enum dynamicWaveFormType
{
	DYNAMICWAVE_SINE,
	DYNAMICWAVE_SAW,
	DYNAMICWAVE_TRI,
	DYNAMICWAVE_RECT,
	DYNAMICWAVE_SAW2
};

class DynamicWaves2: public Plugin<DynamicWaves2>
{
	public:
		DynamicWaves2(double rate);
		void run(uint32_t nframes);

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

		const SynthData *synthdata;
};

#endif
