#include <lvtk-1/lvtk/plugin.hpp>

#include "amplitude.hpp"
#include "amplitude_ttl.hpp"

Amplitude::Amplitude(double rate): Plugin<Amplitude>(p_n_ports)
{
}

void Amplitude::run(uint32_t nframes)
{
	if(*p(p_oldMin) == *p(p_oldMax))
	{
		for (unsigned int l2 = 0; l2 < nframes; l2++)
			p(p_output)[l2] = 0;
		return;
	}

	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_output)[l2] = ((p(p_input)[l2] - *p(p_oldMin)) / (*p(p_oldMax) - *p(p_oldMin))) * (*p(p_newMax) - *p(p_newMin)) + *p(p_newMin);
}

static int _ = Amplitude::register_class("http://github.com/blablack/ams-lv2/amplitude");

