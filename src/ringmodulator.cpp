#include <lvtk-1/lvtk/plugin.hpp>

#include "ringmodulator.hpp"
#include "ringmodulator_ttl.hpp"

RingModulator::RingModulator(double rate): Plugin<RingModulator>(p_n_ports)
{
	gain = 0.5;
}

void RingModulator::run(uint32_t nframes)
{
	gain = *p(p_gain);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_output)[l2] = gain * p(p_carrier)[l2] * p(p_modulation)[l2];
}

static int _ = RingModulator::register_class("http://github.com/blablack/ams-lv2/ringmodulator");

