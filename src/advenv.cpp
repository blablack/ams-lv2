#include <lvtk-1/lvtk/plugin.hpp>

#include "advenv.hpp"
#include "advenv_ttl.hpp"

#define ADVENVELOPE_RESPONSE 256

AdvEnv::AdvEnv(double rate): Plugin<AdvEnv>(p_n_ports)
{
	attack[0] = 0;
	attack[1] = 0.05;
	attack[2] = 0.5;
	attack[3] = 0.05;
	attack[4] = 1.0;
	attack[5] = 0.05;
	attack[6] = 0.9;
	attack[7] = 0.1;
	sustain = 0.7;
	release[0] = 0.05;
	release[1] = 0.5;
	release[2] = 0.05;
	release[3] = 0.2;
	release[4] = 0.05;
	timeScale = 1.0;

	noteActive = false;
	gate = false;
	retrigger = false;
	noteOnOfs = 0;
	noteOffOfs = 0;
	e = 0;
	de = 0;

	m_rate = rate;
}

void AdvEnv::run(uint32_t nframes)
{
	int status;
	float tscale, de_a[4], de_d[3];
	float t[8];

	gateData = p(p_gate);
	retriggerData = p(p_retrigger);

	timeScale = *p(p_timeScale);
	sustain = *p(p_sustain);
	attack[0] = *p(p_delay);
	attack[1] = *p(p_attackTime1);
	attack[2] = *p(p_attackLevel1);
	attack[3] = *p(p_attackTime2);
	attack[4] = *p(p_attackLevel2);
	attack[5] = *p(p_attackTime3);
	attack[6] = *p(p_attackLevel3);
	attack[7] = *p(p_attackTime4);
	release[0] = *p(p_releaseTime1);
	release[1] = *p(p_releaseLevel1);
	release[2] = *p(p_releaseTime2);
	release[3] = *p(p_releaseLevel2);
	release[4] = *p(p_releaseTime3);

	tscale = timeScale * m_rate;
	de_a[0] = (attack[1] > 0) ? attack[2] / (tscale * attack[1]) : 0;
	de_a[1] = (attack[3] > 0) ? (attack[4] - attack[2]) / (tscale * attack[3]) : 0;
	de_a[2] = (attack[5] > 0) ? (attack[6] - attack[4]) / (tscale * attack[5]) : 0;
	de_a[3] = (attack[7] > 0) ? (sustain - attack[6]) / (tscale * attack[7]) : 0;
	de_d[0] = (release[0] > 0) ? (release[1] - sustain) / (tscale * release[0]) : 0;
	de_d[1] = (release[2] > 0) ? (release[3] - release[1]) / (tscale * release[2]) : 0;
	de_d[2] = (release[4] > 0) ? - release[3] / (tscale * release[4]) : 0;
	t[0] = tscale * attack[0];
	t[1] = t[0] + tscale * attack[1];
	t[2] = t[1] + tscale * attack[3];
	t[3] = t[2] + tscale * attack[5];
	t[4] = t[3] + tscale * attack[7];
	t[5] = tscale * release[0];
	t[6] = t[5] + tscale * release[2];
	t[7] = t[6] + tscale * release[4];

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		if (!gate && (gateData[l2] > 0.5)) {
			gate = true;
			noteActive = true;
			if (e > 0)
			{
				noteOnOfs = -ADVENVELOPE_RESPONSE;
				de = e / (float)ADVENVELOPE_RESPONSE;
			}
			else
			{
				noteOnOfs = 0;
			}
		}
		if (gate && (gateData[l2] < 0.5))
		{
			gate = false;
			noteOffOfs = 0;
			e_noteOff = e;
			de_release = (release[0] > 0) ? (release[1] - e_noteOff) / (tscale * release[0]) : 0;
		}
		if (!retrigger && (retriggerData[l2] > 0.5))
		{
			retrigger = true;
			if (e > 0)
			{
				noteOnOfs = -ADVENVELOPE_RESPONSE;
				de = e / (float)ADVENVELOPE_RESPONSE;
			}
			else
			{
				noteOnOfs = 0;
			}
		}
		if (retrigger && (retriggerData[l2] < 0.5))
		{
			retrigger = false;
		}
		if (gate)
		{
			status = 1;
			if (noteOnOfs < 0) status = 0;
			if (noteOnOfs >= long(t[0])) status = 2;
			if (noteOnOfs >= long(t[1])) status = 3;
			if (noteOnOfs >= long(t[2])) status = 4;
			if (noteOnOfs >= long(t[3])) status = 5;
			if (noteOnOfs >= long(t[4])) status = 6;
			switch (status)
			{
				case 0: e -= de;
					break;
				case 1: e = 0;
					break;
				case 2: e += de_a[0];
					break;
				case 3: e += de_a[1];
					break;
				case 4: e += de_a[2];
					break;
				case 5: e += de_a[3];
					break;
				case 6: e = sustain;
					break;
				default: e = 0;
					break;
			}
			if (e < 0) e = 0;
			p(p_out)[l2] = e;
			p(p_invOut)[l2] = -e;
			noteOnOfs++;
		}
		else
		{                          // Release
			if (noteActive)
			{
				status = 1;
				if (noteOffOfs < 0) status = 0;
				if (noteOffOfs >= long(t[5])) status = 2;
				if (noteOffOfs >= long(t[6])) status = 3;
				if (noteOffOfs >= long(t[7])) status = 4;
				switch (status)
				{
					case 0: e = 0;
						break;
					case 1: e += de_release;
						break;
					case 2: e += de_d[1];
						break;
					case 3: e += de_d[2];
						break;
					case 4: e = 0;
						break;
					default: e = 0;
						break;
				}
				if (e < 0)
				{
					e = 0;
				}
				noteOffOfs++;
				if (noteOffOfs >= int(t[7]))
				{
					noteActive = false;
				}
			}
			p(p_out)[l2] = e;
			p(p_invOut)[l2] = -e;
		}
	}
}

static int _ = AdvEnv::register_class("http://github.com/blablack/ams-lv2/advenv");
