#ifndef STEREOMIXER_8CH_H
#define STEREOMIXER_8CH_H

#include <lvtk-1/lvtk/plugin.hpp>

using namespace lvtk;

class StereoMixer8Ch : public Plugin<StereoMixer8Ch>
{
	public:
		StereoMixer8Ch(double rate);
		void run(uint32_t nframes);
};

#endif
