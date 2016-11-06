#include <math.h>
#include <lvtk-1/lvtk/plugin.hpp>

#include "vcenv.hpp"
#include "vcenv_ttl.hpp"

VCEnv::VCEnv(double rate): Plugin<VCEnv> (p_n_ports)
{
	m_rate = rate;

	e = 0;
	old_e = 0;
	state = 0;
	noteActive = false;
	gate = false;
	retrigger = false;
}

void VCEnv::run(uint32_t nframes)
{
	int l2, l2_out;
	double ts, tsr, tsn, tmp, c, n, de;
	int k, len;

	switch((int)(*p(p_timescale))) {
		case 0: ts = 0.1;
			break;
		default:
		case 1: ts = 1.0;
			break;
		case 2: ts = 10.0;
			break;
	}
	tsr = 16.0 * ts / m_rate;
	tsn = ts * m_rate / 16.0;

	len = nframes;
	old_e = e;
	l2 = -1;
	l2_out = 0;
	do {
		k = (len > 24) ? 16 : len;
		l2 += k;
		len -= k;
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
			case 1: e += ((tmp = *p(p_attackOffset) + *p(p_attackGain) * p(p_attack)[l2]) > 0.001) ? tsr / tmp : tsr / 0.001;
				if (e >= 1.0) {
					state = 2;
					e = 1.0;
				}
				break;
			case 2: if ((int)(*p(p_decayreleasemode))) {
					n = tsn * (*p(p_decayOffset) + *p(p_decayGain) * p(p_decay)[l2]);
					if (n < 1) n = 1;
					c = 2.3 / n;
					e *= exp(-c);
				} else {
					e -= ((tmp = *p(p_decayOffset) + *p(p_decayGain) * p(p_decay)[l2]) > 0.001) ? tsr / tmp : tsr / 0.001;
				}
				if (e <= *p(p_sustainOffset) + *p(p_sustainGain) * p(p_sustain)[l2] + 1e-20) {
					state = 3;
				} else {
					break;
				}
			case 3: e = *p(p_sustainOffset) + *p(p_sustainGain) * p(p_sustain)[l2];
				break;
			case 4: if ((int)(*p(p_decayreleasemode))) {
					n = tsn * (*p(p_releaseOffset) + *p(p_releaseGain) * p(p_release)[l2]);
					if (n < 1) n = 1;
					c = 2.3 / n;
					e *= exp(-c);
				} else {
					e -= ((tmp = *p(p_releaseOffset) + *p(p_releaseGain) * p(p_release)[l2]) > 0.001) ? tsr / tmp : tsr / 0.001;

				}
				if (e <= 1e-20) {
					e = 0;
					noteActive = false;
				}
				break;
			default: e = 0;
		}
		de = (e - old_e) / (double)k;
		while (k--) {
			old_e += de;
			p(p_out)[l2_out++] = old_e;
		}
	} while(len);
}

static int _ = VCEnv::register_class("http://github.com/blablack/ams-lv2/vcenv");

