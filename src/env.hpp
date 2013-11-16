#ifndef ENV_H
#define ENV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "env_ttl.hpp"

using namespace lvtk;

#define ENVELOPE_RESPONSE               256

class Env: public Plugin<Env>
{
	private:
		float e_noteOff, de;

		double m_rate;

	public:
		float e;
		bool gate, retrigger;
		//bool attack, hold, release, decay, sustain, delay, retrigger2;
		int noteOnOfs;

		Env(double rate);
		void run(uint32_t nframes);
};

#endif
