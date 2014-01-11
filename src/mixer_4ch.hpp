#ifndef MIXER_4CH_H
#define MIXER_4CH_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_4ch_ttl.hpp"

using namespace lvtk;

class Mixer4Ch : public Plugin<Mixer4Ch>
{
	public:
		Mixer4Ch(double rate);
		void run(uint32_t nframes);
};

#endif
