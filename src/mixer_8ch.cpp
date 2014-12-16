#include <lvtk-1/lvtk/plugin.hpp>

#include "mixer_8ch.hpp"
#include "mixer_8ch_ttl.hpp"

Mixer8Ch::Mixer8Ch(double rate): Plugin<Mixer8Ch>(p_n_ports)
{
}

void Mixer8Ch::run(uint32_t nframes)
{
	float mixgain1 = *p(p_gain) * *p(p_volume1);
	float mixgain2 = *p(p_gain) * *p(p_volume2);
	float mixgain3 = *p(p_gain) * *p(p_volume3);
	float mixgain4 = *p(p_gain) * *p(p_volume4);
	float mixgain5 = *p(p_gain) * *p(p_volume5);
	float mixgain6 = *p(p_gain) * *p(p_volume6);
	float mixgain7 = *p(p_gain) * *p(p_volume7);
	float mixgain8 = *p(p_gain) * *p(p_volume8);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_out)[l2]  = mixgain1 * p(p_in1)[l2]
						+ mixgain2 * p(p_in2)[l2]
						+ mixgain3 * p(p_in3)[l2]
						+ mixgain4 * p(p_in4)[l2]
						+ mixgain5 * p(p_in5)[l2]
						+ mixgain6 * p(p_in6)[l2]
						+ mixgain7 * p(p_in7)[l2]
						+ mixgain8 * p(p_in8)[l2];
}

static int _ = Mixer8Ch::register_class("http://github.com/blablack/ams-lv2/mixer_8ch");

