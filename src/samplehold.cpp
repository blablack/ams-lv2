#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "samplehold.hpp"

using namespace lvtk;

SampleHold::SampleHold(double rate) :
		Plugin<SampleHold>(p_n_ports)
{
	triggerLevel = 0.5;
	gate = false;
}

void SampleHold::run(uint32_t nframes)
{
	unsigned int l2;

	triggerLevel = *p(p_triggerlevel);

	for (l2 = 0; l2 < nframes; l2++)
	{
		if (!gate && (p(p_trigger)[l2] > triggerLevel))
		{
			sample = p(p_input)[l2];
			gate = true;
		}
		else
		{
			gate = p(p_trigger)[l2] > triggerLevel;
		}
		p(p_output)[l2] = sample;
		p(p_gate)[l2] = (gate) ? 1 : 0;
	}
}

static int _ = SampleHold::register_class("http://github.com/blablack/ams-lv2/samplehold");

