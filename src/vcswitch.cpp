#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcswitch.hpp"
#include "vcswitch_ttl.hpp"

VCSwitch::VCSwitch(double rate): Plugin<VCSwitch>(p_n_ports)
{
	switchlevel = 0.5;
}

void VCSwitch::run(uint32_t nframes)
{
	float mix1, mix2;

	switchlevel = *p(p_switchLevel);

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		if (p(p_cv)[l2] > switchlevel)
		{
			p(p_out1)[l2] = p(p_in2)[l2];
			p(p_out2)[l2] = p(p_in1)[l2];
		}
		else
		{
			p(p_out1)[l2] = p(p_in1)[l2];
			p(p_out2)[l2] = p(p_in2)[l2];
		}
		mix1 = p(p_cv)[l2];
		mix2 = 2.0 * switchlevel - mix1;
		if (mix2 < 0)
		{
			mix2 = 0;
			mix1 = 2.0 * switchlevel;
		}
		p(p_outMix)[l2] = (mix1 * p(p_in1)[l2] + mix2 * p(p_in2)[l2]) / (mix1 + mix2);
	}
}

static int _ = VCSwitch::register_class("http://github.com/blablack/ams-lv2/vcswitch");

