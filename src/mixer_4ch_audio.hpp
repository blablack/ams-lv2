#ifndef MIXER_4CH_AUDIO_H
#define MIXER_4CH_AUDIO_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_4ch_audio_ttl.hpp"

using namespace lvtk;

class Mixer4ChAudio : public Plugin<Mixer4ChAudio>
{
	public:
		Mixer4ChAudio(double rate);
		void run(uint32_t nframes);
};

#endif
