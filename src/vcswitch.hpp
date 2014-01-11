#ifndef VCSWITCH_H
#define VCSWITCH_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcswitch_ttl.hpp"

using namespace lvtk;

class VCSwitch: public Plugin<VCSwitch>
{
	private:
		float switchlevel;
	public:
		VCSwitch(double rate);
		void run(uint32_t nframes);
};

#endif
