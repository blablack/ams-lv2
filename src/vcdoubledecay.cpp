#include<math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcdoubledecay.hpp"
#include "vcdoubledecay_ttl.hpp"

VCDoubleDecay::VCDoubleDecay(double rate): Plugin<VCDoubleDecay> (p_n_ports)
{
	synthdata = &SynthData::instance();

	e = 0;
	e2 = 0;
	old_e = 0;
	old_e2 = 0;
	s = 0;
	old_s = 0;

	state = 0;

	noteActive = false;
	gate = false;
	retrigger = false;

	m_rate = rate;
}

void VCDoubleDecay::run(uint32_t nframes)
{
	int l2, k, len, l2_out;
	double ts, tsr, tsn, tmp, c1, c2, n1, n, c, astep, de, de2, ds;

	ts = 1.0;
	tsr = 16.0 * ts / m_rate;
	tsn = ts * m_rate / 16.0;

	len = nframes;
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
			state = 3;
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
		s = *p(p_sustainOffset) + *p(p_sustainGain) * p(p_sustain)[l2];
		switch (state) {
			case 0: e = 0;
				e2 = 0;
				break;
			case 1: astep = ((tmp = synthdata->exp2_table(*p(p_attackOffset) + *p(p_attackGain) * p(p_attack)[l2])) > 0.001) ? tsr / tmp : tsr / 0.001;
				e += astep;
				e2 += astep;
				if (e >= 1.0) {
					state = 2;
					e = 1.0;
				}
				if (e2 >= 1.0) {
					e2 = 1.0;
				}
				break;
			case 2: n1 = tsn * synthdata->exp2_table(*p(p_decayOffset) + *p(p_decayGain) * p(p_decay)[l2]);
				if (n1 < 1) n1 = 1;
				c1 = 2.3 / n1;
				c2 = c1 * (*p(p_ratioOffset) + *p(p_ratioGain) * p(p_ratio)[l2]);
				if (c2 < 0) c2 = 0;
				e *= exp(-c1);
				if (e <= 1e-20) e = 0;
				e2 *= exp(-c2);
				if (e2 <= 1e-20) e2 = 0;
				break;
			case 3: n = tsn * synthdata->exp2_table(*p(p_releaseOffset) + *p(p_releaseGain) * p(p_release)[l2]);
				if (n < 1) n = 1;
				c = 2.3 / n;
				e *= exp(-c);
				if (e <= 1e-20) e = 0;
				e2 *= exp(-c);
				if (e2 < 1e-20)  {
					e = 0;
					e2 = 0;
					noteActive = false;
				}
				break;
			default: e = 0;
				e2 = 0;
				p(p_output)[l2] = e;
		}

		de = (e - old_e) / (double)k;
		de2 = (e2 - old_e2) / (double)k;
		ds = (s - old_s) / (double)k;
		while (k--) {
			old_e += de;
			old_e2 += de2;
			old_s += ds;
			p(p_output)[l2_out++] = (1.0 - old_s) * old_e + old_s * old_e2;
		}
	} while (len);
}

static int _ = VCDoubleDecay::register_class("http://github.com/blablack/ams-lv2/vcdoubledecay");

