#ifndef MIXER_2CH_CV_H
#define MIXER_2CH_CV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_2ch_cv_ttl.hpp"

using namespace lvtk;

class Mixer2ChCV : public Plugin<Mixer2ChCV>
{
	public:
		Mixer2ChCV(double rate);
		void run(uint32_t nframes);
};

#endif
