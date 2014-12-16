#include <lvtk-1/lvtk/plugin.hpp>

#include "stereomixer_8ch.hpp"
#include "stereomixer_8ch_ttl.hpp"

StereoMixer8Ch::StereoMixer8Ch(double rate): Plugin<StereoMixer8Ch>(p_n_ports)
{
}

void StereoMixer8Ch::run(uint32_t nframes)
{
	bool p_atLeastOneSolo = *p(p_solo1) > 0.5 ||
							*p(p_solo2) > 0.5 ||
							*p(p_solo3) > 0.5 ||
							*p(p_solo4) > 0.5 ||
							*p(p_solo5) > 0.5 ||
							*p(p_solo6) > 0.5 ||
							*p(p_solo7) > 0.5 ||
							*p(p_solo8) > 0.5;

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

	float mixgain3_L, mixgain3_R;
	if(*p(p_mute3) > 0.5 || (p_atLeastOneSolo && *p(p_solo3) < 0.5))
	{
		mixgain3_L = 0.0;
		mixgain3_R = 0.0;
	}
	else
	{
		mixgain3_L = *p(p_masterVolume) * (1.0 - *p(p_pan3)) * *p(p_volume3);
		mixgain3_R = *p(p_masterVolume) * (1.0 + *p(p_pan3)) * *p(p_volume3);
	}

	float mixgain4_L, mixgain4_R;
	if(*p(p_mute4) > 0.5 || (p_atLeastOneSolo && *p(p_solo4) < 0.5))
	{
		mixgain4_L = 0.0;
		mixgain4_R = 0.0;
	}
	else
	{
		mixgain4_L = *p(p_masterVolume) * (1.0 - *p(p_pan4)) * *p(p_volume4);
		mixgain4_R = *p(p_masterVolume) * (1.0 + *p(p_pan4)) * *p(p_volume4);
	}

	float mixgain5_L, mixgain5_R;
	if(*p(p_mute5) > 0.5 || (p_atLeastOneSolo && *p(p_solo5) < 0.5))
	{
		mixgain5_L = 0.0;
		mixgain5_R = 0.0;
	}
	else
	{
		mixgain5_L = *p(p_masterVolume) * (1.0 - *p(p_pan5)) * *p(p_volume5);
		mixgain5_R = *p(p_masterVolume) * (1.0 + *p(p_pan5)) * *p(p_volume5);
	}

	float mixgain6_L, mixgain6_R;
	if(*p(p_mute6) > 0.5 || (p_atLeastOneSolo && *p(p_solo6) < 0.5))
	{
		mixgain6_L = 0.0;
		mixgain6_R = 0.0;
	}
	else
	{
		mixgain6_L = *p(p_masterVolume) * (1.0 - *p(p_pan6)) * *p(p_volume6);
		mixgain6_R = *p(p_masterVolume) * (1.0 + *p(p_pan6)) * *p(p_volume6);
	}

	float mixgain7_L, mixgain7_R;
	if(*p(p_mute7) > 0.5 || (p_atLeastOneSolo && *p(p_solo7) < 0.5))
	{
		mixgain7_L = 0.0;
		mixgain7_R = 0.0;
	}
	else
	{
		mixgain7_L = *p(p_masterVolume) * (1.0 - *p(p_pan7)) * *p(p_volume7);
		mixgain7_R = *p(p_masterVolume) * (1.0 + *p(p_pan7)) * *p(p_volume7);
	}

	float mixgain8_L, mixgain8_R;
	if(*p(p_mute8) > 0.5 || (p_atLeastOneSolo && *p(p_solo8) < 0.5))
	{
		mixgain8_L = 0.0;
		mixgain8_R = 0.0;
	}
	else
	{
		mixgain8_L = *p(p_masterVolume) * (1.0 - *p(p_pan8)) * *p(p_volume8);
		mixgain8_R = *p(p_masterVolume) * (1.0 + *p(p_pan8)) * *p(p_volume8);
	}


	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_outL)[l2] = mixgain1_L * p(p_in1)[l2] +
						mixgain2_L * p(p_in2)[l2] +
						mixgain3_L * p(p_in3)[l2] +
						mixgain4_L * p(p_in4)[l2] +
						mixgain5_L * p(p_in5)[l2] +
						mixgain6_L * p(p_in6)[l2] +
						mixgain7_L * p(p_in7)[l2] +
						mixgain8_L * p(p_in8)[l2];

		p(p_outR)[l2] = mixgain1_R * p(p_in1)[l2] +
						mixgain2_R * p(p_in2)[l2] +
						mixgain3_R * p(p_in3)[l2] +
						mixgain4_R * p(p_in4)[l2] +
						mixgain5_R * p(p_in5)[l2] +
						mixgain6_R * p(p_in6)[l2] +
						mixgain7_R * p(p_in7)[l2] +
						mixgain8_R * p(p_in8)[l2];
	}
}

static int _ = StereoMixer8Ch::register_class("http://github.com/blablack/ams-lv2/stereomixer_8ch");

