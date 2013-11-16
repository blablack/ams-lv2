#ifndef VCPANNING_H
#define VCPANNING_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcpanning_ttl.hpp"

using namespace lvtk;

class VCPanning: public Plugin<VCPanning>
{
	private:
		float panPos, pan[2], oldpan[2];
	public:
		VCPanning(double rate);
		void run(uint32_t nframes);

};

#endif
