#ifndef AD_H
#define AD_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"
#include "ad_ttl.hpp"

using namespace lvtk;

class Ad: public Plugin<Ad>
{
	private:
		float detune_a, detune_c;
		float drift_a[MAX_ANALOGUE_DRIVER_OUT], drift_c[MAX_ANALOGUE_DRIVER_OUT];
		int detuneCount, driftCount, voice[2];
		double m_rate;
		SynthData *synthdata;

	public:
		Ad(double rate);
		void run(uint32_t nframes);
};

#endif
