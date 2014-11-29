#ifndef STEREOMIXER_2CH_H
#define STEREOMIXER_2CH_H

#include <lvtk-1/lvtk/plugin.hpp>
#include "stereomixer_2ch_ttl.hpp"

using namespace lvtk;

class StereoMixer2Ch : public Plugin<StereoMixer2Ch>
{
	public:
		StereoMixer2Ch(double rate);
		void run(uint32_t nframes);
};

#endif
