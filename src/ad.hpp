#ifndef AD_H
#define AD_H

#include "synthdata.hpp"

#if OUT_COUNT == 2
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	2
#elif OUT_COUNT == 4
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	4
#elif OUT_COUNT == 6
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	6
#endif

using namespace lvtk;

class Ad: public Plugin<Ad>
{
	public:
		Ad(double rate);
		void run(uint32_t nframes);

	private:
		float detune_a, detune_c;
		float drift_a[MAX_ANALOGUE_DRIVER_OUT], drift_c[MAX_ANALOGUE_DRIVER_OUT];
		int detuneCount, driftCount;
		double m_rate;
		const SynthData *synthdata;
};

#endif
