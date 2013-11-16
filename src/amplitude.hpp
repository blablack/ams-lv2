#ifndef AMPLITUDE_H
#define AMPLITUDE_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "amplitude_ttl.hpp"

using namespace lvtk;

class Amplitude: public Plugin<Amplitude>
{
	public:
		Amplitude(double rate);
		void run(uint32_t nframes);
};

#endif
