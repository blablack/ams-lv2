#ifndef MIXER_2CH_H
#define MIXER_2CH_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_2ch_ttl.hpp"

using namespace lvtk;

class Mixer2Ch : public Plugin<Mixer2Ch>
{
	public:
		Mixer2Ch(double rate);
		void run(uint32_t nframes);
};

#endif
