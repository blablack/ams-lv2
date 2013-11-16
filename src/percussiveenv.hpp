#ifndef PERCUSSIVEENV_H
#define PERCUSSIVEENV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "percussiveenv_ttl.hpp"

using namespace lvtk;

#define ENVELOPE_RESPONSE               256

class PercussiveEnv: public Plugin<PercussiveEnv>
{
	private:
		float e;
		bool trigger, triggered;
		int noteOnOfs;

		double m_rate;

	public:
		PercussiveEnv(double rate);
		void run(uint32_t nframes);
};

#endif
