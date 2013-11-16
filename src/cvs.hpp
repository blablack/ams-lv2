#ifndef CVS_H
#define CVS_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "cvs_ttl.hpp"

using namespace lvtk;

class Cvs: public Plugin<Cvs>
{
	public:
		Cvs(double rate);
		void run(uint32_t nframes);
};

#endif
