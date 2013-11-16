#ifndef INV_H
#define INV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "inv_ttl.hpp"

using namespace lvtk;


class Inv
: public Plugin<Inv>
{

public:
	Inv(double rate);
	void run(uint32_t nframes);
};

#endif
