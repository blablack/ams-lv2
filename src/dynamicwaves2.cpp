#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "dynamicwaves2.hpp"

#if OSC_COUNT == 4
#include "dynamicwaves2_4_ttl.hpp"
#elif OSC_COUNT == 6
#include "dynamicwaves2_6_ttl.hpp"
#elif OSC_COUNT == 8
#include "dynamicwaves2_8_ttl.hpp"
#endif

#define DYNAMICWAVES_ENVELOPE_RESPONSE	256

DynamicWaves2::DynamicWaves2(double rate): Plugin<DynamicWaves2> (p_n_ports)
{
	synthdata = &SynthData::instance();

	wave_period = (float) WAVE_PERIOD;
	wave_period_2 = wave_period / 2.0;

	m_rate = rate;

	allEnvTerminated = true;
	noteActive = false;
	gate = false;
	retrigger = false;

	for (int i = 0 ; i < MODULE_DYNAMICWAVES_OSC ; i++)
	{
		oscActive[i] = false;
		e[i] = 0;
		noteOnOfs[i] = 0;
		noteOffOfs[i] = 0;
		e_noteOff[i] = 0;
		de[i] = 0;
		de_release[i] = 0;
		phi[i] = 0;
	}
}

void DynamicWaves2::run(uint32_t nframes)
{
	int l3, l4, status;
	float dphi, phi1;
	float freq_const[MODULE_DYNAMICWAVES_OSC], freq_tune[MODULE_DYNAMICWAVES_OSC];
	float gain_linfm, current_gain;
	float gain_const[MODULE_DYNAMICWAVES_OSC], phi_const[MODULE_DYNAMICWAVES_OSC];
	float t[8][MODULE_DYNAMICWAVES_OSC], tscale;
	float de_a[4][MODULE_DYNAMICWAVES_OSC];
	float de_d[3][MODULE_DYNAMICWAVES_OSC];

	freqData = p(p_freq);
	expFMData = p(p_expFM);
	linFMData = p(p_linFM);
	gateData = p(p_gate);
	retriggerData = p(p_retrigger);

	gain_linfm = 1000.0 * *p(p_linFMGain);
	tscale = *p(p_timeScale) * m_rate;

#if OSC_COUNT == 4
	float gain[MODULE_DYNAMICWAVES_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4)};
	float osc_octave[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave)};
	float osc_tune[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune)};
	float semitone[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_semitone), *p(p_vco2_semitone), *p(p_vco3_semitone), *p(p_vco4_semitone)};
	float phi0[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0)};

	float attack[8][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_delay), *p(p_env2_delay), *p(p_env3_delay), *p(p_env4_delay)},
		{*p(p_env1_attackTime1), *p(p_env2_attackTime1), *p(p_env3_attackTime1), *p(p_env4_attackTime1)},
		{*p(p_env1_attackLevel1), *p(p_env2_attackLevel1), *p(p_env3_attackLevel1), *p(p_env4_attackLevel1)},
		{*p(p_env1_attackTime2), *p(p_env2_attackTime2), *p(p_env3_attackTime2), *p(p_env4_attackTime2)},
		{*p(p_env1_attackLevel2), *p(p_env2_attackLevel2), *p(p_env3_attackLevel2), *p(p_env4_attackLevel2)},
		{*p(p_env1_attackTime3), *p(p_env2_attackTime3), *p(p_env3_attackTime3), *p(p_env4_attackTime3)},
		{*p(p_env1_attackLevel3), *p(p_env2_attackLevel3), *p(p_env3_attackLevel3), *p(p_env4_attackLevel3)},
		{*p(p_env1_attackTime4), *p(p_env2_attackTime4), *p(p_env3_attackTime4), *p(p_env4_attackTime4)}
	};

	float sustain[MODULE_DYNAMICWAVES_OSC] = {*p(p_env1_sustain), *p(p_env2_sustain), *p(p_env3_sustain), *p(p_env4_sustain)};

	float release[5][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_releaseTime1), *p(p_env2_releaseTime1), *p(p_env3_releaseTime1), *p(p_env4_releaseTime1)},
		{*p(p_env1_releaseLevel1), *p(p_env2_releaseLevel1), *p(p_env3_releaseLevel1), *p(p_env4_releaseLevel1)},
		{*p(p_env1_releaseTime2), *p(p_env2_releaseTime2), *p(p_env3_releaseTime2), *p(p_env4_releaseTime2)},
		{*p(p_env1_releaseLevel2), *p(p_env2_releaseLevel2), *p(p_env3_releaseLevel2), *p(p_env4_releaseLevel2)},
		{*p(p_env1_releaseTime3), *p(p_env2_releaseTime3), *p(p_env3_releaseTime3), *p(p_env4_releaseTime3)}
	};

	int waveForm[MODULE_DYNAMICWAVES_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm))};
#elif OSC_COUNT == 6
	float gain[MODULE_DYNAMICWAVES_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4), *p(p_volume5), *p(p_volume6)};
	float osc_octave[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave), *p(p_vco5_octave), *p(p_vco6_octave)};
	float osc_tune[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune), *p(p_vco5_tune), *p(p_vco6_tune)};
	float semitone[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_semitone), *p(p_vco2_semitone), *p(p_vco3_semitone), *p(p_vco4_semitone), *p(p_vco5_semitone), *p(p_vco6_semitone)};
	float phi0[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0), *p(p_vco5_phi0), *p(p_vco6_phi0)};

	float attack[8][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_delay), *p(p_env2_delay), *p(p_env3_delay), *p(p_env4_delay), *p(p_env5_delay), *p(p_env6_delay)},
		{*p(p_env1_attackTime1), *p(p_env2_attackTime1), *p(p_env3_attackTime1), *p(p_env4_attackTime1), *p(p_env5_attackTime1), *p(p_env6_attackTime1)},
		{*p(p_env1_attackLevel1), *p(p_env2_attackLevel1), *p(p_env3_attackLevel1), *p(p_env4_attackLevel1), *p(p_env5_attackLevel1), *p(p_env6_attackLevel1)},
		{*p(p_env1_attackTime2), *p(p_env2_attackTime2), *p(p_env3_attackTime2), *p(p_env4_attackTime2), *p(p_env5_attackTime2), *p(p_env6_attackTime2)},
		{*p(p_env1_attackLevel2), *p(p_env2_attackLevel2), *p(p_env3_attackLevel2), *p(p_env4_attackLevel2), *p(p_env5_attackLevel2), *p(p_env6_attackLevel2)},
		{*p(p_env1_attackTime3), *p(p_env2_attackTime3), *p(p_env3_attackTime3), *p(p_env4_attackTime3), *p(p_env5_attackTime3), *p(p_env6_attackTime3)},
		{*p(p_env1_attackLevel3), *p(p_env2_attackLevel3), *p(p_env3_attackLevel3), *p(p_env4_attackLevel3), *p(p_env5_attackLevel3), *p(p_env6_attackLevel3)},
		{*p(p_env1_attackTime4), *p(p_env2_attackTime4), *p(p_env3_attackTime4), *p(p_env4_attackTime4), *p(p_env5_attackTime4), *p(p_env6_attackTime4)}
	};

	float sustain[MODULE_DYNAMICWAVES_OSC] = {*p(p_env1_sustain), *p(p_env2_sustain), *p(p_env3_sustain), *p(p_env4_sustain), *p(p_env5_sustain), *p(p_env6_sustain)};

	float release[5][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_releaseTime1), *p(p_env2_releaseTime1), *p(p_env3_releaseTime1), *p(p_env4_releaseTime1), *p(p_env5_releaseTime1), *p(p_env6_releaseTime1)},
		{*p(p_env1_releaseLevel1), *p(p_env2_releaseLevel1), *p(p_env3_releaseLevel1), *p(p_env4_releaseLevel1), *p(p_env5_releaseLevel1), *p(p_env6_releaseLevel1)},
		{*p(p_env1_releaseTime2), *p(p_env2_releaseTime2), *p(p_env3_releaseTime2), *p(p_env4_releaseTime2), *p(p_env5_releaseTime2), *p(p_env6_releaseTime2)},
		{*p(p_env1_releaseLevel2), *p(p_env2_releaseLevel2), *p(p_env3_releaseLevel2), *p(p_env4_releaseLevel2), *p(p_env5_releaseLevel2), *p(p_env6_releaseLevel2)},
		{*p(p_env1_releaseTime3), *p(p_env2_releaseTime3), *p(p_env3_releaseTime3), *p(p_env4_releaseTime3), *p(p_env5_releaseTime3), *p(p_env6_releaseTime3)}
	};

	int waveForm[MODULE_DYNAMICWAVES_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm)), (int)(*p(p_vco5_waveForm)), (int)(*p(p_vco6_waveForm))};
#elif OSC_COUNT == 8
	float gain[MODULE_DYNAMICWAVES_OSC] = {*p(p_volume1), *p(p_volume2), *p(p_volume3), *p(p_volume4), *p(p_volume5), *p(p_volume6), *p(p_volume7), *p(p_volume8)};
	float osc_octave[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_octave), *p(p_vco2_octave), *p(p_vco3_octave), *p(p_vco4_octave), *p(p_vco5_octave), *p(p_vco6_octave), *p(p_vco7_octave), *p(p_vco8_octave)};
	float osc_tune[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_tune), *p(p_vco2_tune), *p(p_vco3_tune), *p(p_vco4_tune), *p(p_vco5_tune), *p(p_vco6_tune), *p(p_vco7_tune), *p(p_vco8_tune)};
	float semitone[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_semitone), *p(p_vco2_semitone), *p(p_vco3_semitone), *p(p_vco4_semitone), *p(p_vco5_semitone), *p(p_vco6_semitone), *p(p_vco7_semitone), *p(p_vco8_semitone)};
	float phi0[MODULE_DYNAMICWAVES_OSC] = {*p(p_vco1_phi0), *p(p_vco2_phi0), *p(p_vco3_phi0), *p(p_vco4_phi0), *p(p_vco5_phi0), *p(p_vco6_phi0), *p(p_vco7_phi0), *p(p_vco8_phi0)};

	float attack[8][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_delay), *p(p_env2_delay), *p(p_env3_delay), *p(p_env4_delay), *p(p_env5_delay), *p(p_env6_delay), *p(p_env7_delay), *p(p_env8_delay)},
		{*p(p_env1_attackTime1), *p(p_env2_attackTime1), *p(p_env3_attackTime1), *p(p_env4_attackTime1), *p(p_env5_attackTime1), *p(p_env6_attackTime1), *p(p_env7_attackTime1), *p(p_env8_attackTime1)},
		{*p(p_env1_attackLevel1), *p(p_env2_attackLevel1), *p(p_env3_attackLevel1), *p(p_env4_attackLevel1), *p(p_env5_attackLevel1), *p(p_env6_attackLevel1), *p(p_env7_attackLevel1), *p(p_env8_attackLevel1)},
		{*p(p_env1_attackTime2), *p(p_env2_attackTime2), *p(p_env3_attackTime2), *p(p_env4_attackTime2), *p(p_env5_attackTime2), *p(p_env6_attackTime2), *p(p_env7_attackTime2), *p(p_env8_attackTime2)},
		{*p(p_env1_attackLevel2), *p(p_env2_attackLevel2), *p(p_env3_attackLevel2), *p(p_env4_attackLevel2), *p(p_env5_attackLevel2), *p(p_env6_attackLevel2), *p(p_env7_attackLevel2), *p(p_env8_attackLevel2)},
		{*p(p_env1_attackTime3), *p(p_env2_attackTime3), *p(p_env3_attackTime3), *p(p_env4_attackTime3), *p(p_env5_attackTime3), *p(p_env6_attackTime3), *p(p_env7_attackTime3), *p(p_env8_attackTime3)},
		{*p(p_env1_attackLevel3), *p(p_env2_attackLevel3), *p(p_env3_attackLevel3), *p(p_env4_attackLevel3), *p(p_env5_attackLevel3), *p(p_env6_attackLevel3), *p(p_env7_attackLevel3), *p(p_env8_attackLevel3)},
		{*p(p_env1_attackTime4), *p(p_env2_attackTime4), *p(p_env3_attackTime4), *p(p_env4_attackTime4), *p(p_env5_attackTime4), *p(p_env6_attackTime4), *p(p_env7_attackTime4), *p(p_env8_attackTime4)}
	};

	float sustain[MODULE_DYNAMICWAVES_OSC] = {*p(p_env1_sustain), *p(p_env2_sustain), *p(p_env3_sustain), *p(p_env4_sustain), *p(p_env5_sustain), *p(p_env6_sustain), *p(p_env7_sustain), *p(p_env8_sustain)};

	float release[5][MODULE_DYNAMICWAVES_OSC] =
	{
		{*p(p_env1_releaseTime1), *p(p_env2_releaseTime1), *p(p_env3_releaseTime1), *p(p_env4_releaseTime1), *p(p_env5_releaseTime1), *p(p_env6_releaseTime1), *p(p_env7_releaseTime1), *p(p_env8_releaseTime1)},
		{*p(p_env1_releaseLevel1), *p(p_env2_releaseLevel1), *p(p_env3_releaseLevel1), *p(p_env4_releaseLevel1), *p(p_env5_releaseLevel1), *p(p_env6_releaseLevel1), *p(p_env7_releaseLevel1), *p(p_env8_releaseLevel1)},
		{*p(p_env1_releaseTime2), *p(p_env2_releaseTime2), *p(p_env3_releaseTime2), *p(p_env4_releaseTime2), *p(p_env5_releaseTime2), *p(p_env6_releaseTime2), *p(p_env7_releaseTime2), *p(p_env8_releaseTime2)},
		{*p(p_env1_releaseLevel2), *p(p_env2_releaseLevel2), *p(p_env3_releaseLevel2), *p(p_env4_releaseLevel2), *p(p_env5_releaseLevel2), *p(p_env6_releaseLevel2), *p(p_env7_releaseLevel2), *p(p_env8_releaseLevel2)},
		{*p(p_env1_releaseTime3), *p(p_env2_releaseTime3), *p(p_env3_releaseTime3), *p(p_env4_releaseTime3), *p(p_env5_releaseTime3), *p(p_env6_releaseTime3), *p(p_env7_releaseTime3), *p(p_env8_releaseTime3)}
	};

	int waveForm[MODULE_DYNAMICWAVES_OSC] = {(int)(*p(p_vco1_waveForm)), (int)(*p(p_vco2_waveForm)), (int)(*p(p_vco3_waveForm)), (int)(*p(p_vco4_waveForm)), (int)(*p(p_vco5_waveForm)), (int)(*p(p_vco6_waveForm)), (int)(*p(p_vco7_waveForm)), (int)(*p(p_vco8_waveForm))};
#endif


	for (l3 = 0; l3 < MODULE_DYNAMICWAVES_OSC; l3++) {
		gain_const[l3] = gain[l3] / (float)MODULE_DYNAMICWAVES_OSC;
		freq_tune[l3] = 4.0313842 + *p(p_octave) + *p(p_tune) + osc_octave[l3] + osc_tune[l3];
		freq_const[l3] = wave_period / (float)m_rate * ((float)semitone[l3] / 12.0f);
		phi_const[l3] = phi0[l3] * wave_period / (2.0 * M_PI);
		de_a[0][l3] = (attack[1][l3] > 0) ? attack[2][l3] / (tscale * attack[1][l3]) : 0;
		de_a[1][l3] = (attack[3][l3] > 0) ? (attack[4][l3] - attack[2][l3]) / (tscale * attack[3][l3]) : 0;
		de_a[2][l3] = (attack[5][l3] > 0) ? (attack[6][l3] - attack[4][l3]) / (tscale * attack[5][l3]) : 0;
		de_a[3][l3] = (attack[7][l3] > 0) ? (sustain[l3] - attack[6][l3]) / (tscale * attack[7][l3]) : 0;
		de_d[0][l3] = (release[0][l3] > 0) ? (release[1][l3] - sustain[l3]) / (tscale * release[0][l3]) : 0;
		de_d[1][l3] = (release[2][l3] > 0) ? (release[3][l3] - release[1][l3]) / (tscale * release[2][l3]) : 0;
		de_d[2][l3] = (release[4][l3] > 0) ? - release[3][l3] / (tscale * release[4][l3]) : 0;
		t[0][l3] = tscale * attack[0][l3];
		t[1][l3] = t[0][l3] + tscale * attack[1][l3];
		t[2][l3] = t[1][l3] + tscale * attack[3][l3];
		t[3][l3] = t[2][l3] + tscale * attack[5][l3];
		t[4][l3] = t[3][l3] + tscale * attack[7][l3];
		t[5][l3] = tscale * release[0][l3];
		t[6][l3] = t[5][l3] + tscale * release[2][l3];
		t[7][l3] = t[6][l3] + tscale * release[4][l3];
	}

	for (unsigned int l2 = 0; l2 < nframes; l2++) {
		noteActive = !allEnvTerminated;
		allEnvTerminated = true;
		if (!retrigger && (retriggerData[l2] > 0.5)) {
			retrigger = true;
		}
		if (retrigger && (retriggerData[l2] < 0.5)) {
			retrigger = false;
		}

		for (l3 = 0; l3 < MODULE_DYNAMICWAVES_OSC; l3++) {
			if (l3 == 0) {
				if (!gate && (gateData[l2] > 0.5)) {
					gate = true;
					noteActive = true;
					for (l4 = 0; l4 < MODULE_DYNAMICWAVES_OSC; l4++) {
						oscActive[l4] = true;
						if (e[l4] > 0) {
							noteOnOfs[l4] = -DYNAMICWAVES_ENVELOPE_RESPONSE;
							de[l4] = e[l4] / (float)DYNAMICWAVES_ENVELOPE_RESPONSE;
						} else {
							noteOnOfs[l4] = 0;
						}
					}
				}
				if (gate && (gateData[l2] < 0.5)) {
					gate = false;
					for (l4 = 0; l4 < MODULE_DYNAMICWAVES_OSC; l4++) {
						noteOffOfs[l4] = 0;
						e_noteOff[l4] = e[l4];
						de_release[l4] = (release[0][l4] > 0) ? (release[1][l4] - e_noteOff[l4]) / (tscale * release[0][l4]) : 0;
					}
				}
			}
			if (retrigger) {
				if (e[l3] > 0) {
					noteOnOfs[l3] = 0;
					if (e[l3] < attack[2][l3]) {
						noteOnOfs[l3] = (de_a[0][l3] > 0) ? t[0][l3] + e[l3] / de_a[0][l3] : t[0][l3];
					} else if (e[l3] < attack[4][l3]) {
						noteOnOfs[l3] = (de_a[1][l3] > 0) ? t[1][l3] + (e[l3] - attack[2][l3]) / de_a[1][l3] : t[1][l3];
					} else if (e[l3] < attack[6][l3]) {
						noteOnOfs[l3] = (de_a[2][l3] > 0) ? t[2][l3] + (e[l3] - attack[4][l3]) / de_a[2][l3] : t[2][l3];
					} else if (e[l3] <= sustain[l3]) {
						noteOnOfs[l3] = (de_a[3][l3] > 0) ? t[3][l3] + (e[l3] - attack[6][l3]) / de_a[3][l3] : t[3][l3];
					}
				} else {
					noteOnOfs[l3] = 0;
				}
			}
			if (gate) {
				status = 1;
				if (noteOnOfs[l3] < 0) status = 0;
				if (noteOnOfs[l3] >= long(t[0][l3])) status = 2;
				if (noteOnOfs[l3] >= long(t[1][l3])) status = 3;
				if (noteOnOfs[l3] >= long(t[2][l3])) status = 4;
				if (noteOnOfs[l3] >= long(t[3][l3])) status = 5;
				if (noteOnOfs[l3] >= long(t[4][l3])) status = 6;
				switch (status) {
					case 0: e[l3] -= de[l3];
						break;
					case 1: e[l3] = 0;
						break;
					case 2: e[l3] += de_a[0][l3];
						break;
					case 3: e[l3] += de_a[1][l3];
						break;
					case 4: e[l3] += de_a[2][l3];
						break;
					case 5: e[l3] += de_a[3][l3];
						break;
					case 6: e[l3] = sustain[l3];
						break;
					default: e[l3] = 0;
						break;
				}
				if (e[l3] < 0) e[l3] = 0;
				noteOnOfs[l3]++;
			} else {
				if (oscActive[l3] > 0) {
					status = 1;
					if (noteOffOfs[l3] < 0) status = 0;
					if (noteOffOfs[l3] >= long(t[5][l3])) status = 2;
					if (noteOffOfs[l3] >= long(t[6][l3])) status = 3;
					if (noteOffOfs[l3] >= long(t[7][l3])) status = 4;
					switch (status) {
						case 0: e[l3] = 0;
							break;
						case 1: e[l3] += de_release[l3];
							break;
						case 2: e[l3] += de_d[1][l3];
							break;
						case 3: e[l3] += de_d[2][l3];
							break;
						case 4: e[l3] = 0;
							break;
						default: e[l3] = 0;
							break;
					}
					if (e[l3] < 0) e[l3] = 0;
				}
				noteOffOfs[l3]++;
				if (noteOffOfs[l3] >= int(t[7][l3])) {
					oscActive[l3] = false;
					e[l3] = 0;
				}
			}
			if (oscActive[l3]) {
				allEnvTerminated = false;
			}
			dphi = freq_const[l3] * (synthdata->exp2_table(freq_tune[l3] + freqData[l2] + *p(p_expFMGain) * expFMData[l2])
									 + gain_linfm * linFMData[l2]);
			if (dphi > wave_period_2) {
				dphi = wave_period_2;
				current_gain = 0;
			} else {
				current_gain = gain_const[l3] * e[l3];
			}

			phi1 = phi[l3] + phi_const[l3];
			if (phi1 < 0) phi1 += wave_period;
			else if (phi1 >= wave_period) phi1 -= wave_period;
			switch (waveForm[l3]) {
				case DYNAMICWAVE_SINE:
					p(p_out)[l2] += current_gain * synthdata->wave_sine[(int)phi1];
					break;
				case DYNAMICWAVE_SAW:
					p(p_out)[l2] += current_gain * synthdata->wave_saw[(int)phi1];
					break;
				case DYNAMICWAVE_TRI:
					p(p_out)[l2] += current_gain * synthdata->wave_tri[(int)phi1];
					break;
				case DYNAMICWAVE_RECT:
					p(p_out)[l2] += current_gain * synthdata->wave_rect[(int)phi1];
					break;
				case DYNAMICWAVE_SAW2:
					p(p_out)[l2] += current_gain * synthdata->wave_saw2[(int)phi1];
					break;
			}
			phi[l3] += dphi;
			while (phi[l3] < 0) phi[l3] += wave_period;
			while (phi[l3] >= wave_period) phi[l3] -= wave_period;
		}
	}
}

#if OSC_COUNT == 4
	static int _ = DynamicWaves2::register_class("http://github.com/blablack/ams-lv2/dynamicwaves2_4");
#elif OSC_COUNT == 6
	static int _ = DynamicWaves2::register_class("http://github.com/blablack/ams-lv2/dynamicwaves2_6");
#elif OSC_COUNT == 8
	static int _ = DynamicWaves2::register_class("http://github.com/blablack/ams-lv2/dynamicwaves2_8");
#endif
