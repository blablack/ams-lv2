#include <lvtk-1/lvtk/plugin.hpp>

#include "absolute.hpp"
#include "absolute_ttl.hpp"

Absolute::Absolute(double rate): Plugin<Absolute>(p_n_ports)
{
}

void Absolute::run(uint32_t nframes)
{
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		if(p(p_input)[l2] < 0)
			p(p_output)[l2] = p(p_input)[l2] * -1;
		else
			p(p_output)[l2] = p(p_input)[l2];
	}
}

static int _ = Absolute::register_class("http://github.com/blablack/ams-lv2/absolute");

