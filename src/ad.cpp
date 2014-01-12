#include <math.h>
#include <lvtk-1/lvtk/plugin.hpp>

#include "ad.hpp"

using namespace lvtk;

Ad::Ad(double rate) :
	Plugin<Ad> (p_n_ports)
{
	int outCount = 2;
	int l1;

	for (l1 = 0; l1 < outCount; l1++)
	{
		drift_a[l1] = 0.4 * (double) random() / (double) RAND_MAX - 0.2;
		drift_c[l1] = 0.4 * (double) random() / (double) RAND_MAX - 0.2;
	}
	detune_a = 0.4 * (double) random() / (double) RAND_MAX - 0.2;
	detune_c = 0.4 * (double) random() / (double) RAND_MAX - 0.2;

	detuneCount = 0;
	driftCount = 0;

	m_rate = rate;
	synthdata = new SynthData();
}

void Ad::run(uint32_t nframes)
{
	int l3, l5;
	uint32_t l2;
	float dta, dra, rdt, rdr;
	double qdt, qdr;

	dta = *p(p_detuneAmplitude);
	dra = *p(p_driftAmplitude);
	rdt = *p(p_detuneModulation) / (float) m_rate;
	rdr = *p(p_driftModulation) / (float) m_rate;
	qdt = (double) 2 * m_rate / (*p(p_detuneRate) + 1e-3);
	qdr = (double) 2 * m_rate / (*p(p_detuneRate) + 1e-3);
	for (l3 = 0; l3 < 2; l3++)
	{
		for (l2 = 0; l2 < nframes; l2++)
		{
			switch (l3)
			{
				case 0:
					p(p_cvOut0)[l2] = p(p_cvIn)[l2] + dta * detune_a + dra * drift_a[l3];
					break;
				case 1:
					p(p_cvOut1)[l2] = p(p_cvIn)[l2] + dta * detune_a + dra * drift_a[l3];
					break;
			}

			detune_a += rdt * detune_c;
			if (detune_a > 1.0)
			{
				detune_a = 1.0;
				detune_c = -1.0;
			}
			else if (detune_a < -1.0)
			{
				detune_a = -1.0;
				detune_c = 1.0;
			}

			if (drift_a[l3] > 1.0)
			{
				drift_a[l3] = 1.0;
				drift_c[l3] = -1.0;
			}
			else if (drift_a[l3] < -1.0)
			{
				drift_a[l3] = -1.0;
				drift_c[l3] = 1.0;
			}

			drift_a[l3] += rdr * drift_c[l3];
			detuneCount++;
			driftCount++;
			if (detuneCount > qdt)
			{
				detuneCount = 0;
				detune_c = 2.0 * (double) random() / (double) RAND_MAX - 1.0;
			}
			if (driftCount > qdr)
			{
				driftCount = 0;
				for (l5 = 0; l5 < 2; l5++)
				{
					drift_c[l5] = 2.0 * (double) random() / (double) RAND_MAX - 1.0;
				}
			}
		}
	}
}

static int _ = Ad::register_class("http://github.com/blablack/ams-lv2/ad");

