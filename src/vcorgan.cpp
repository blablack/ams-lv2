#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcorgan.hpp"
#if OSC_COUNT == 4
#include "vcorgan_4_ttl.hpp"
#elif OSC_COUNT == 6
#include "vcorgan_6_ttl.hpp"
#elif OSC_COUNT == 8
#include "vcorgan_8_ttl.hpp"
#endif

#define VCORGAN_EXP_TABLE_LEN 32768

VCOrgan::VCOrgan(double rate):	Plugin<VCOrgan> (p_n_ports)
{
	synthdata = &SynthData::instance();

	wave_period = (float) WAVE_PERIOD;
	wave_period_2 = wave_period / 2.0;

	m_rate = rate;

	for (int i = 0 ; i < MODULE_VCORGAN_OSC ; i++)
	{
		phi[i] = 0;
	}
}

void VCOrgan::run(uint32_t nframes)
{
	int l3;
	float dphi, phi1;
	float freq_const[MODULE_VCORGAN_OSC], freq_tune[MODULE_VCORGAN_OSC];
	float gain_linfm, current_gain;
	float gain_const[MODULE_VCORGAN_OSC], phi_const[MODULE_VCORGAN_OSC];

	freqData = p(p_freq);
	expFMData = p(p_expFM);
	linFMData = p(p_linFM);

	gain_linfm = 1000.0 * *p(p_linFMGain);

#if OSC_COUNT == 4
	float gain[MODULE_VCORGAN_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4)};
	float osc_octave[MODULE_VCORGAN_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave)};
	float osc_tune[MODULE_VCORGAN_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune)};
	float harmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_harmonic), *p(p_vco2_harmonic), *p(p_vco3_harmonic), *p(p_vco4_harmonic)};
	float subharmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_subharmonic), *p(p_vco2_subharmonic), *p(p_vco3_subharmonic), *p(p_vco4_subharmonic)};
	float phi0[MODULE_VCORGAN_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0)};

	int waveForm[MODULE_VCORGAN_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm))};
#elif OSC_COUNT == 6
	float gain[MODULE_VCORGAN_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4), *p(p_volume5), *p(p_volume6)};
	float osc_octave[MODULE_VCORGAN_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave), *p(p_vco5_octave), *p(p_vco6_octave)};
	float osc_tune[MODULE_VCORGAN_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune), *p(p_vco5_tune), *p(p_vco6_tune)};
	float harmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_harmonic), *p(p_vco2_harmonic), *p(p_vco3_harmonic), *p(p_vco4_harmonic), *p(p_vco5_harmonic), *p(p_vco6_harmonic)};
	float subharmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_subharmonic), *p(p_vco2_subharmonic), *p(p_vco3_subharmonic), *p(p_vco4_subharmonic), *p(p_vco5_subharmonic), *p(p_vco6_subharmonic)};
	float phi0[MODULE_VCORGAN_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0), *p(p_vco5_phi0), *p(p_vco6_phi0)};

	int waveForm[MODULE_VCORGAN_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm)), (int)(*p(p_vco5_waveForm)), (int)(*p(p_vco6_waveForm))};
#elif OSC_COUNT == 8
	float gain[MODULE_VCORGAN_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4), *p(p_volume5), *p(p_volume6), *p(p_volume7), *p(p_volume8)};
	float osc_octave[MODULE_VCORGAN_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave), *p(p_vco5_octave), *p(p_vco6_octave), *p(p_vco7_octave), *p(p_vco8_octave)};
	float osc_tune[MODULE_VCORGAN_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune), *p(p_vco5_tune), *p(p_vco6_tune), *p(p_vco7_tune), *p(p_vco8_tune)};
	float harmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_harmonic), *p(p_vco2_harmonic), *p(p_vco3_harmonic), *p(p_vco4_harmonic), *p(p_vco5_harmonic), *p(p_vco6_harmonic), *p(p_vco7_harmonic), *p(p_vco8_harmonic)};
	float subharmonic[MODULE_VCORGAN_OSC] = {*p(p_vco1_subharmonic), *p(p_vco2_subharmonic), *p(p_vco3_subharmonic), *p(p_vco4_subharmonic), *p(p_vco5_subharmonic), *p(p_vco6_subharmonic), *p(p_vco7_subharmonic), *p(p_vco8_subharmonic)};
	float phi0[MODULE_VCORGAN_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0), *p(p_vco5_phi0), *p(p_vco6_phi0), *p(p_vco7_phi0), *p(p_vco8_phi0)};

	int waveForm[MODULE_VCORGAN_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm)), (int)(*p(p_vco5_waveForm)), (int)(*p(p_vco6_waveForm)), (int)(*p(p_vco7_waveForm)), (int)(*p(p_vco8_waveForm))};
#endif


	for (l3 = 0; l3 < MODULE_VCORGAN_OSC; l3++)
	{
		gain_const[l3] = gain[l3] / (float)MODULE_VCORGAN_OSC;
		freq_tune[l3] = 4.0313842 + *p(p_octave) + *p(p_tune) + osc_octave[l3] + osc_tune[l3];
		freq_const[l3] = wave_period / (float)m_rate * (float)harmonic[l3] / (float)subharmonic[l3];
		phi_const[l3] = phi0[l3] * wave_period / (2.0 * M_PI);
	}


	for (l3 = 0; l3 < MODULE_VCORGAN_OSC; l3++)
	{
		if (phi0[l3] == 0)
		{
			for (unsigned int l2 = 0; l2 < nframes; l2++)
			{
				dphi = freq_const[l3] * (synthdata->exp2_table(freq_tune[l3] + freqData[l2] + *p(p_expFMGain) * expFMData[l2]) + gain_linfm * linFMData[l2]);
				if (dphi > wave_period_2)
				{
					dphi = wave_period_2;
					current_gain = 0;
				}
				else
				{
					current_gain = gain_const[l3];
				}
				switch (waveForm[l3])
				{
					case ORGAN_SINE:
						p(p_out)[l2] += current_gain * synthdata->wave_sine[(int)phi[l3]];
						break;
					case ORGAN_SAW:
						p(p_out)[l2] += current_gain * synthdata->wave_saw[(int)phi[l3]];
						break;
					case ORGAN_TRI:
						p(p_out)[l2] += current_gain * synthdata->wave_tri[(int)phi[l3]];
						break;
					case ORGAN_RECT:
						p(p_out)[l2] += current_gain * synthdata->wave_rect[(int)phi[l3]];
						break;
					case ORGAN_SAW2:
						p(p_out)[l2] += current_gain * synthdata->wave_saw2[(int)phi[l3]];
						break;
				}
				phi[l3] += dphi;
				while (phi[l3] < 0) phi[l3] += wave_period;
				while (phi[l3] >= wave_period) phi[l3] -= wave_period;
			}
		}
		else
		{
			for (unsigned int l2 = 0; l2 < nframes; l2++)
			{
				dphi = freq_const[l3] * (synthdata->exp2_table(freq_tune[l3] + freqData[l2] + *p(p_expFMGain) * expFMData[l2]) + gain_linfm * linFMData[l2]);
				if (dphi > wave_period_2)
				{
					dphi = wave_period_2;
					current_gain = 0;
				}
				else
				{
					current_gain = gain_const[l3];
				}
				phi1 = phi[l3] + phi_const[l3];
				if (phi1 < 0) phi1 += wave_period;
				else if (phi1 >= wave_period) phi1 -= wave_period;
				switch (waveForm[l3])
				{
					case ORGAN_SINE:
						p(p_out)[l2] += current_gain * synthdata->wave_sine[(int)phi1];
						break;
					case ORGAN_SAW:
						p(p_out)[l2] += current_gain * synthdata->wave_saw[(int)phi1];
						break;
					case ORGAN_TRI:
						p(p_out)[l2] += current_gain * synthdata->wave_tri[(int)phi1];
						break;
					case ORGAN_RECT:
						p(p_out)[l2] += current_gain * synthdata->wave_rect[(int)phi1];
						break;
					case ORGAN_SAW2:
						p(p_out)[l2] += current_gain * synthdata->wave_saw2[(int)phi1];
						break;
				}
				phi[l3] += dphi;
				while (phi[l3] < 0) phi[l3] += wave_period;
				while (phi[l3] >= wave_period) phi[l3] -= wave_period;
			}
		}
	}
}

#if OSC_COUNT == 4
static int _ = VCOrgan::register_class("http://github.com/blablack/ams-lv2/vcorgan_4");
#elif OSC_COUNT == 6
static int _ = VCOrgan::register_class("http://github.com/blablack/ams-lv2/vcorgan_6");
#elif OSC_COUNT == 8
static int _ = VCOrgan::register_class("http://github.com/blablack/ams-lv2/vcorgan_8");
#endif




