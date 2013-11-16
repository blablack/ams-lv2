#ifndef VCAEXP_AUDIO_H
#define VCAEXP_AUDIO_H

#include "synthdata.hpp"

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcaexp_audio_ttl.hpp"

using namespace lvtk;

class VcaExpAudio: public Plugin<VcaExpAudio>
{
	private:
		SynthData *synthdata;

	public:
		VcaExpAudio(double rate);
		void run(uint32_t nframes);
};

#endif
