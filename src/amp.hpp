#ifndef AMP_H
#define AMP_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "amp_ttl.hpp"

using namespace lvtk;

class Amp: public Plugin<Amp>
{
	public:
		Amp(double rate);
		void run(uint32_t nframes);
};

#endif
