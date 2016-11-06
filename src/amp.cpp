#include <lvtk-1/lvtk/plugin.hpp>

#include "amp.hpp"
#include "amp_ttl.hpp"

Amp::Amp(double rate): Plugin<Amp>(p_n_ports)
{
}

void Amp::run(uint32_t nframes)
{
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_output)[l2] = *p(p_gain) * p(p_input)[l2];
}

static int _ = Amp::register_class("http://github.com/blablack/ams-lv2/amp");

