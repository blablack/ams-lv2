#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcenvii.hpp"
#include "vcenvii_ttl.hpp"

VCEnvII::VCEnvII(double rate): Plugin<VCEnvII> (p_n_ports)
{
	synthdata = &SynthData::instance();

	m_rate = rate;

	e = 0;
	old_e = 0;
	state = 0;
	noteActive = false;
	gate = false;
	retrigger = false;
}

void VCEnvII::run(uint32_t nframes)
{
	unsigned int l2;
	double ts, tsr, tsn, tmp, c, n;

	ts = 1.0;
	tsr = ts / m_rate;
	tsn = ts * m_rate;
	for (l2 = 0; l2 < nframes; l2++) {
		if (!gate && p(p_gate)[l2] > 0.5) {
			gate = true;
			noteActive = true;
			state = 1;
		}
		if (gate && p(p_gate)[l2] < 0.5) {
			gate = false;
			state = 4;
		}
		if (!retrigger && p(p_retrigger)[l2] > 0.5) {
			retrigger = true;
			if (gate) {
				state = 1;
			}
		}
		if (retrigger && p(p_retrigger)[l2] < 0.5) {
			retrigger = false;
		}
		switch (state) {
			case 0: e = 0;
				break;
			case 1: e += ((tmp = synthdata->exp2_table(*p(p_attackOffset) + *p(p_attackGain) * p(p_attack)[l2])) > 0.001) ? tsr / tmp : tsr / 0.001;
				if (e >= 1.0) {
					state = 2;
					e = 1.0;
				}
				break;
			case 2: n = tsn * synthdata->exp2_table(*p(p_decayOffset) + *p(p_decayGain) * p(p_decay)[l2]);
				if (n < 1) n = 1;
				c = 2.3 / n;
				e *= exp(-c);
				if (e <= *p(p_sustainOffset) + *p(p_sustainGain) * p(p_sustain)[l2] + 1e-20) {
					state = 3;
				} else {
					break;
				}
			case 3: e = *p(p_sustainOffset) + *p(p_sustainGain) * p(p_sustain)[l2];
				break;
			case 4: n = tsn * synthdata->exp2_table(*p(p_releaseOffset) + *p(p_releaseGain) * p(p_release)[l2]);
				if (n < 1) n = 1;
				c = 2.3 / n;
				e *= exp(-c);
				if (e <= 1e-20) {
					e = 0;
					noteActive = false;
				}
				break;
			default: e = 0;
		}
		p(p_out)[l2] = e;
	}
}

static int _ = VCEnvII::register_class("http://github.com/blablack/ams-lv2/vcenvii");

