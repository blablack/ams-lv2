#ifndef MIXER_8CH_H
#define MIXER_8CH_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_8ch_ttl.hpp"

using namespace lvtk;

class Mixer8Ch : public Plugin<Mixer8Ch>
{
	public:
		Mixer8Ch(double rate);
		void run(uint32_t nframes);
};

#endif
