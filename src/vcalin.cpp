#include <lvtk-1/lvtk/plugin.hpp>

#include "vcalin.hpp"
#include "vcalin_ttl.hpp"

VcaLin::VcaLin(double rate): Plugin<VcaLin>(p_n_ports)
{
}

void VcaLin::run(uint32_t nframes)
{
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_out)[l2] = (*p(p_gain1) + p(p_gain1Data)[l2] + *p(p_gain2) * p(p_gain2Data)[l2]) * *p(p_outputLevel) * (*p(p_in1) * p(p_in1Data)[l2] + *p(p_in2) * p(p_in2Data)[l2]);
}

static int _ = VcaLin::register_class("http://github.com/blablack/ams-lv2/vcalin");

