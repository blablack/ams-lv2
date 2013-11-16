#ifndef RINGMODULATOR_H
#define RINGMODULATOR_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "ringmodulator_audio_ttl.hpp"

using namespace lvtk;

class RingModulatorAudio: public Plugin<RingModulatorAudio>
{
	private:
		float gain;
	public:
		RingModulatorAudio(double rate);
		void run(uint32_t nframes);
};

#endif
