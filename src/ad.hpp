#ifndef AD_H
#define AD_H

#include <lvtk-1/lvtk/plugin.hpp>
#include "synthdata.hpp"

#if OUT_COUNT == 2
#include "ad_2_ttl.hpp"
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	2
#elif OUT_COUNT == 4
#include "ad_4_ttl.hpp"
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	4
#elif OUT_COUNT == 6
#include "ad_6_ttl.hpp"
#undef MAX_ANALOGUE_DRIVER_OUT
#define MAX_ANALOGUE_DRIVER_OUT	6
#endif


using namespace lvtk;

class Ad: public Plugin<Ad>
{
	private:
		float detune_a, detune_c;
		float drift_a[MAX_ANALOGUE_DRIVER_OUT], drift_c[MAX_ANALOGUE_DRIVER_OUT];
		//int detuneCount, driftCount, voice[2];
		int detuneCount, driftCount;
		double m_rate;
		SynthData *synthdata;

	public:
		Ad(double rate);
		void run(uint32_t nframes);
};

#endif
