#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcswitch_cv.hpp"

using namespace lvtk;

VCSwitchCV::VCSwitchCV(double rate) :
		Plugin<VCSwitchCV>(p_n_ports)
{
	switchlevel = 0.5;
}

void VCSwitchCV::run(uint32_t nframes)
{
	unsigned int l2;
	float mix1, mix2;

	switchlevel = *p(p_switchlevel);

	for (l2 = 0; l2 < nframes; l2++)
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
		p(p_outmix)[l2] = (mix1 * p(p_in1)[l2] + mix2 * p(p_in2)[l2]) / (mix1 + mix2);
	}
}

static int _ = VCSwitchCV::register_class("http://github.com/blablack/ams.lv2/vcswitch_cv");

