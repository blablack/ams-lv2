#ifndef VCSWITCH_AUDIO_H
#define VCSWITCH_AUDIO_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcswitch_audio_ttl.hpp"

using namespace lvtk;

class VCSwitchAudio: public Plugin<VCSwitchAudio>
{
	private:
		float switchlevel;
	public:
		VCSwitchAudio(double rate);
		void run(uint32_t nframes);
};

#endif
