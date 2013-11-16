#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "mixer_2ch_audio.hpp"

using namespace lvtk;

Mixer2ChAudio::Mixer2ChAudio(double rate)
: Plugin<Mixer2ChAudio>(p_n_ports)
  {
  }

void Mixer2ChAudio::run(uint32_t nframes)
{
	float mixgain1 = *p(p_gain) * *p(p_volume1);
	float mixgain2 = *p(p_gain) * *p(p_volume2);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  = mixgain1 * p(p_in1)[l2] + mixgain2 * p(p_in2)[l2];
	}
}

static int _ = Mixer2ChAudio::register_class("http://github.com/blablack/ams.lv2/mixer_2ch_audio");

