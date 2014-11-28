#ifndef STEREOMIXER_4CH_H
#define STEREOMIXER_4CH_H

#include <lvtk-1/lvtk/plugin.hpp>

using namespace lvtk;

class StereoMixer4Ch : public Plugin<StereoMixer4Ch>
{
	public:
		StereoMixer4Ch(double rate);
		void run(uint32_t nframes);
};

#endif
