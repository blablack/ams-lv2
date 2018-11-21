#include <lvtk-1/lvtk/plugin.hpp>

#include "vcaexp.hpp"
#include "vcaexp_ttl.hpp"

VcaExp::VcaExp(double rate): Plugin<VcaExp>(p_n_ports)
{
	synthdata = &SynthData::instance();
}

void VcaExp::run(uint32_t nframes)
{
	float v, g;

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		v = *p(p_gain1) + p(p_gain1Data)[l2] + *p(p_gain2) * p(p_gain2Data)[l2];
		g = (v > 0) ? synthdata->exp_table ((v - 1.0) * 9.21) : 0;  // This gives a range of 80 dB
		p(p_out)[l2] = g * *p(p_outputLevel) * (*p(p_in1) * p(p_in1Data)[l2] + *p(p_in2) * p(p_in2Data)[l2]);
	}
}

static int _ = VcaExp::register_class("http://github.com/blablack/ams-lv2/vcaexp");
