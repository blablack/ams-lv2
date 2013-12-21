#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "ringmodulator_audio.hpp"

using namespace lvtk;

RingModulatorAudio::RingModulatorAudio(double rate)
:Plugin<RingModulatorAudio>(p_n_ports)
 {
	gain = 0.5;
 }

void RingModulatorAudio::run(uint32_t nframes)
{
	gain = *p(p_gain);
	unsigned int l2;
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_output)[l2] = gain * p(p_carrier)[l2] * p(p_modulation)[l2];
	}
}

static int _ = RingModulatorAudio::register_class("http://github.com/blablack/ams-lv2/ringmodulator_audio");

