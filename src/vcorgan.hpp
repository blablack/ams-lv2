#ifndef VCORGAN_H
#define VCORGAN_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"

#if OSC_COUNT == 4
	#include "vcorgan_4_ttl.hpp"
	#undef MODULE_VCORGAN_OSC
	#define MODULE_VCORGAN_OSC	4
#elif OSC_COUNT == 6
	#include "vcorgan_6_ttl.hpp"
	#undef MODULE_VCORGAN_OSC
	#define MODULE_VCORGAN_OSC	6
#elif OSC_COUNT == 8
	#include "vcorgan_8_ttl.hpp"
	#undef MODULE_VCORGAN_OSC
	#define MODULE_VCORGAN_OSC	8
#endif

#define VCORGAN_EXP_TABLE_LEN             32768

using namespace lvtk;

enum waveFormType
{
	ORGAN_SINE,
	ORGAN_SAW,
	ORGAN_TRI,
	ORGAN_RECT,
	ORGAN_SAW2
};


class VCOrgan: public Plugin<VCOrgan>
{
	private:
		double m_rate;
		float wave_period, wave_period_2;

		float phi[MODULE_VCORGAN_OSC];

		float *freqData;
		float *expFMData;
		float *linFMData;

		SynthData *synthdata;

	public:
		VCOrgan(double rate);
		void run(uint32_t nframes);
};

#endif
