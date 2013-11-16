#ifndef MIXER_2CH_AUDIO_H
#define MIXER_2CH_AUDIO_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_2ch_audio_ttl.hpp"

using namespace lvtk;

class Mixer2ChAudio : public Plugin<Mixer2ChAudio>
{
	public:
		Mixer2ChAudio(double rate);
		void run(uint32_t nframes);
};

#endif
