#include <lvtk-1/lvtk/plugin.hpp>

#include "hysteresis.hpp"
#include "hysteresis_ttl.hpp"

Hysteresis::Hysteresis(double rate): Plugin<Hysteresis>(p_n_ports)
{
	currentsegment = 0;
}

void Hysteresis::run(uint32_t nframes)
{
	unsigned int l2;

	for (l2 = 0; l2 < nframes; l2++) {
		// Which segment are we on?  Whichever one we were on before,
		// unless we've crossed an edge.
		if (p(p_in)[l2] < (*p(p_center) - *p(p_overlap)))
			currentsegment = 0;
		if (p(p_in)[l2] > (*p(p_center) + *p(p_overlap)))
			currentsegment = 1;
		// Set output values
		if (currentsegment == 0)
			p(p_out)[l2] =  // -1;
						   (p(p_in)[l2] * *p(p_lowSlope))-1;
		if (currentsegment == 1)
			p(p_out)[l2] = // 1;
						  (p(p_in)[l2] * *p(p_highSlope))+1;
	}
}

static int _ = Hysteresis::register_class("http://github.com/blablack/ams-lv2/hysteresis");

