#ifndef VCORGAN2_H
#define VCORGAN2_H

#include "synthdata.hpp"

#if OSC_COUNT == 4
#undef MODULE_VCORGAN_OSC
#define MODULE_VCORGAN_OSC	4
#elif OSC_COUNT == 6
#undef MODULE_VCORGAN_OSC
#define MODULE_VCORGAN_OSC	6
#elif OSC_COUNT == 8
#undef MODULE_VCORGAN_OSC
#define MODULE_VCORGAN_OSC	8
#endif

using namespace lvtk;

enum waveFormType
{
	ORGAN_SINE,
	ORGAN_SAW,
	ORGAN_TRI,
	ORGAN_RECT,
	ORGAN_SAW2
};


class VCOrgan2: public Plugin<VCOrgan2>
{
	public:
		VCOrgan2(double rate);
		void run(uint32_t nframes);

	private:
		double m_rate;
		float wave_period, wave_period_2;

		float phi[MODULE_VCORGAN_OSC];

		float *freqData;
		float *expFMData;
		float *linFMData;

		const SynthData *synthdata;
};

#endif
