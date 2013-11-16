#ifndef MIXER_4CH_CV_H
#define MIXER_4CH_CV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_4ch_cv_ttl.hpp"

using namespace lvtk;

class Mixer4ChCV : public Plugin<Mixer4ChCV>
{
	public:
		Mixer4ChCV(double rate);
		void run(uint32_t nframes);
};

#endif
