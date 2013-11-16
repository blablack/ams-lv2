#ifndef ADVENV_H
#define ADVENV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "advenv_ttl.hpp"

using namespace lvtk;

#define ADVENVELOPE_RESPONSE               256

class AdvEnv: public Plugin<AdvEnv>
{
	private:
		float attack[8], sustain, release[5];
		float e_noteOff, de, de_release;

		double m_rate;

	public:
		float e;
		float timeScale;
		bool noteActive, gate, retrigger;
		int noteOnOfs;
		int noteOffOfs;
		float *gateData, *retriggerData;

		AdvEnv(double rate);
		void run(uint32_t nframes);
};

#endif
