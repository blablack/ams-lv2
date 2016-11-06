#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_4ch.hpp"
#include "mixer_4ch_ttl.hpp"

Mixer4Ch::Mixer4Ch(double rate): Plugin<Mixer4Ch>(p_n_ports)
{
}

void Mixer4Ch::run(uint32_t nframes)
{
	float mixgain1 = *p(p_gain) * *p(p_volume1);
	float mixgain2 = *p(p_gain) * *p(p_volume2);
	float mixgain3 = *p(p_gain) * *p(p_volume3);
	float mixgain4 = *p(p_gain) * *p(p_volume4);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_out)[l2]  = mixgain1 * p(p_in1)[l2] + mixgain2 * p(p_in2)[l2] + mixgain3 * p(p_in3)[l2] + mixgain4 * p(p_in4)[l2];
}

static int _ = Mixer4Ch::register_class("http://github.com/blablack/ams-lv2/mixer_4ch");

