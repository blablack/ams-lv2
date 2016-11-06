#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_2ch.hpp"
#include "mixer_2ch_ttl.hpp"

Mixer2Ch::Mixer2Ch(double rate): Plugin<Mixer2Ch>(p_n_ports)
{
}

void Mixer2Ch::run(uint32_t nframes)
{
	float mixgain1 = *p(p_gain) * *p(p_volume1);
	float mixgain2 = *p(p_gain) * *p(p_volume2);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_out)[l2]  = mixgain1 * p(p_in1)[l2] + mixgain2 * p(p_in2)[l2];
}

static int _ = Mixer2Ch::register_class("http://github.com/blablack/ams-lv2/mixer_2ch");

