#include <lvtk-1/lvtk/plugin.hpp>

#include "stereomixer_2ch.hpp"
#include "stereomixer_2ch_ttl.hpp"

StereoMixer2Ch::StereoMixer2Ch(double rate): Plugin<StereoMixer2Ch>(p_n_ports)
{
}

void StereoMixer2Ch::run(uint32_t nframes)
{
	bool p_atLeastOneSolo = *p(p_solo1) > 0.5 ||
							*p(p_solo2) > 0.5;

	float mixgain1_L, mixgain1_R;
	if(*p(p_mute1) > 0.5 || (p_atLeastOneSolo && *p(p_solo1) < 0.5))
	{
		mixgain1_L = 0.0;
		mixgain1_R = 0.0;
	}
	else
	{
		mixgain1_L = *p(p_masterVolume) * (1.0 - *p(p_pan1)) * *p(p_volume1);
		mixgain1_R = *p(p_masterVolume) * (1.0 + *p(p_pan1)) * *p(p_volume1);
	}

	float mixgain2_L, mixgain2_R;
	if(*p(p_mute2) > 0.5 || (p_atLeastOneSolo && *p(p_solo2) < 0.5))
	{
		mixgain2_L = 0.0;
		mixgain2_R = 0.0;
	}
	else
	{
		mixgain2_L = *p(p_masterVolume) * (1.0 - *p(p_pan2)) * *p(p_volume2);
		mixgain2_R = *p(p_masterVolume) * (1.0 + *p(p_pan2)) * *p(p_volume2);
	}

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_outL)[l2] = mixgain1_L * p(p_in1)[l2] +
						mixgain2_L * p(p_in2)[l2];

		p(p_outR)[l2] = mixgain1_R * p(p_in1)[l2] +
						mixgain2_R * p(p_in2)[l2];
	}
}

static int _ = StereoMixer2Ch::register_class("http://github.com/blablack/ams-lv2/stereomixer_2ch");


