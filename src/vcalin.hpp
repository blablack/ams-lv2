#ifndef VCALIN_H
#define VCALIN_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcalin_ttl.hpp"

using namespace lvtk;

class VcaLin: public Plugin<VcaLin>
{
	public:
		VcaLin(double rate);
		void run(uint32_t nframes);
};

#endif
