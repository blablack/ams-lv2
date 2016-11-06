#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "multiphase_lfo.hpp"
#include "multiphase_lfo_ttl.hpp"

MultiphaseLfo::MultiphaseLfo(double rate): Plugin<MultiphaseLfo>(p_n_ports)
{
	m_rate = rate;
	state = 0;
}

void MultiphaseLfo::run(uint32_t nframes)
{
	int l1;
	unsigned int l2;
	double tri45, tri90, tri135, saw45, saw90, saw135, saw180, saw225, saw270, saw315;
	double sign_saw1, sign_saw2;

	d_saw = 0;
	d_tri = ((state > 1) && (state < 6)) ? -4.0 * *p(p_freq) / m_rate
										 :  4.0 * *p(p_freq) / m_rate;
	d_saw = 0.5 * fabs(d_tri);

	switch((int)(*p(p_sawMode))) {
		case 1:
			sign_saw1 = -1.0;
			sign_saw2 = -1.0;
			break;
		case 2:
			sign_saw1 = 1.0;
			sign_saw2 = -1.0;
			break;
		case 0: // fall through
		default:
			sign_saw1 = 1.0;
			sign_saw2 = 1.0;
			break;
	}

	for (l2 = 0; l2 < nframes; l2++) {
		tri += d_tri;
		saw += d_saw;
		switch(state) {
			case 1:
				if (tri > 1.0) {
					state++;
					tri = 1.0;
					d_tri = -4.0 * *p(p_freq) / m_rate;
					d_saw = -0.5 * d_tri;
				}
				tri45 = 1.5 - tri;
				tri90 = 1.0 - tri;
				tri135 = 0.5 - tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = -1.25 + saw;
				saw180 = -1.0 + saw;
				saw225 = -0.75 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				break;
			case 2:
				if (tri < 0.5) {
					state++;
				}
				tri45 = tri - 0.5;
				tri90 = tri - 1.0;
				tri135 = -1.5 + tri;
				saw45 = 0.25 + saw;
				saw90 = -1.5 + saw;
				saw135 = -1.25 + saw;
				saw180 = -1.0 + saw;
				saw225 = -0.75 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				break;
			case 3:
				tri45 = tri - 0.5;
				tri90 = tri - 1.0;
				tri135 = -0.5 - tri;
				saw45 = -1.75 + saw;
				saw90 = -1.5 + saw;
				saw135 = -1.25 + saw;
				saw180 = -1.0 + saw;
				saw225 = -0.75 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				if (tri < 0.0) {
					state++;
					saw = -1.0;
				}
				break;
			case 4:
				if (tri < -0.5) {
					state++;
				}
				tri45 = tri - 0.5;
				tri90 = -1.0 - tri;
				tri135 = -0.5 - tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = 0.75 + saw;
				saw180 = 1.0 + saw;
				saw225 = 1.25 + saw;
				saw270 = 1.5 + saw;
				saw315 = 1.75 + saw;
				break;
			case 5:
				if (tri < -1.0) {
					tri = -1.0;
					d_tri = 4.0 * *p(p_freq) / m_rate;
					d_saw = 0.5 * d_tri;
					state++;
				}
				tri45 = - 1.5 - tri;
				tri90 = -1.0 - tri;
				tri135 = -0.5 - tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = 0.75 + saw;
				saw180 = 1.0 + saw;
				saw225 = 1.25 + saw;
				saw270 = 1.5 + saw;
				saw315 = -0.25 + saw;
				break;
			case 6:
				if (tri > -0.5) {
					state++;
				}
				tri45 = 0.5 + tri;
				tri90 = 1.0 + tri;
				tri135 = 1.5 + tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = 0.75 + saw;
				saw180 = 1.0 + saw;
				saw225 = 1.25 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				break;
			case 7:
				if (tri > 0.0) {
					state = 0;
				}
				tri45 = 0.5 + tri;
				tri90 = 1.0 + tri;
				tri135 = 0.5 - tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = 0.75 + saw;
				saw180 = 1.0 + saw;
				saw225 = -0.75 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				break;
			case 0: // fall through
			default:
				if (tri > 0.5) {
					state++;
				}
				tri45 = 0.5 + tri;
				tri90 = 1.0 - tri;
				tri135 = 0.5 - tri;
				saw45 = 0.25 + saw;
				saw90 = 0.5 + saw;
				saw135 = 0.75 + saw;
				saw180 = -1.0 + saw;
				saw225 = -0.75 + saw;
				saw270 = -0.5 + saw;
				saw315 = -0.25 + saw;
				break;
		}

		float gain_saw = *p(p_gainSaw);
		p(p_sawOut_0)[l2]	= gain_saw * (1.0 + sign_saw1 * saw45);
		p(p_sawOut_45)[l2]	= gain_saw * (1.0 + sign_saw1 * saw);
		p(p_sawOut_90)[l2]	= gain_saw * (1.0 + sign_saw1 * saw315);
		p(p_sawOut_135)[l2] = gain_saw * (1.0 + sign_saw1 * saw270);
		p(p_sawOut_180)[l2] = gain_saw * (1.0 + sign_saw2 * saw225);
		p(p_sawOut_225)[l2] = gain_saw * (1.0 + sign_saw2 * saw180);
		p(p_sawOut_270)[l2] = gain_saw * (1.0 + sign_saw2 * saw135);
		p(p_sawOut_315)[l2] = gain_saw * (1.0 + sign_saw2 * saw90);

		float gain_tri = *p(p_gainTriangle);
		p(p_triOut_0)[l2]	= gain_tri * (1.0 + tri135);
		p(p_triOut_45)[l2]	= gain_tri * (1.0 + tri90);
		p(p_triOut_90)[l2]	= gain_tri * (1.0 + tri45);
		p(p_triOut_135)[l2] = gain_tri * (1.0 + tri);
		p(p_triOut_180)[l2] = gain_tri * (1.0 - tri135);
		p(p_triOut_225)[l2] = gain_tri * (1.0 - tri90);
		p(p_triOut_270)[l2] = gain_tri * (1.0 - tri45);
		p(p_triOut_315)[l2] = gain_tri * (1.0 - tri);
	}
}

static int _ = MultiphaseLfo::register_class("http://github.com/blablack/ams-lv2/multiphase_lfo");
