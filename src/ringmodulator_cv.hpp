#ifndef RINGMODULATOR_H
#define RINGMODULATOR_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "ringmodulator_cv_ttl.hpp"

using namespace lvtk;

class RingModulatorCV: public Plugin<RingModulatorCV>
{
	private:
		float gain;
	public:
		RingModulatorCV(double rate);
		void run(uint32_t nframes);
};

#endif
