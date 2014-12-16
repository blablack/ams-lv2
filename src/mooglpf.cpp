#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "mooglpf.hpp"
#include "mooglpf_ttl.hpp"

MoogLPF::MoogLPF(double rate): Plugin<MoogLPF>(p_n_ports)
{
	_c1 = _c2 = _c3 = _c4 = _c5 = _w = _r = 0;
	m_rate = rate;
}

float MoogLPF::exp2ap(float x)
{
	int i;

	i = (int) (floor(x));
	x -= i;
	return ldexp(1 + x * (0.6930 + x * (0.2416 + x * (0.0517 + x * 0.0137))), i);
}

void MoogLPF::run(uint32_t nframes)
{
	uint32_t len = nframes;

	int k;
	float *p0, *p1, *p2, *p3, *p4;
	float c1, c2, c3, c4, c5;
	float g0, g1, r, dr, w, dw, x, t, d;

	p0 = p(p_portInput);
	p1 = p(p_output);
	p2 = p(p_portFrequency) - 1;
	p3 = p(p_portExpFM) - 1;
	p4 = p(p_portResonance) - 1;
	g0 = exp2ap(0.1661 * *p(p_inputGain)) / 2;
	g1 = exp2ap(0.1661 * *p(p_outputGain)) * 2;

	c1 = _c1;
	c2 = _c2;
	c3 = _c3;
	c4 = _c4;
	c5 = _c5;
	w = _w;
	r = _r;

	do
	{
		k = (len > 24) ? 16 : len;
		p2 += k;
		p3 += k;
		p4 += k;
		len -= k;

		t = exp2ap(*p(p_expFMGain) * *p3 + *p(p_frequency) + *p2 + 9.70) / m_rate;
		if (t < 0.75)
			t *= 1.005 - t * (0.624 - t * (0.65 - t * 0.54));
		else
		{
			t *= 0.6748;
			if (t > 0.82)
				t = 0.82;
		}
		dw = (t - w) / k;

		t = *p(p_resonanceGain) * *p4 + *p(p_resonance);
		if (t > 1)
			t = 1;
		if (t < 0)
			t = 0;
		dr = (t - r) / k;

		while (k--)
		{
			w += dw;
			r += dr;

			x = *p0 * g0 - (4.3 - 0.2 * w) * r * c5 + 1e-10;
			x /= sqrt(1 + x * x);
			d = w * (x - c1) / (1 + c1 * c1);
			x = c1 + 0.77 * d;
			c1 = x + 0.23 * d;
			d = w * (x - c2) / (1 + c2 * c2);
			x = c2 + 0.77 * d;
			c2 = x + 0.23 * d;
			d = w * (x - c3) / (1 + c3 * c3);
			x = c3 + 0.77 * d;
			c3 = x + 0.23 * d;
			d = w * (x - c4);
			x = c4 + 0.77 * d;
			c4 = x + 0.23 * d;
			c5 += 0.85 * (c4 - c5);

			x = *p0++ * g0 - (4.3 - 0.2 * w) * r * c5;
			x /= sqrt(1 + x * x);
			d = w * (x - c1) / (1 + c1 * c1);
			x = c1 + 0.77 * d;
			c1 = x + 0.23 * d;
			d = w * (x - c2) / (1 + c2 * c2);
			x = c2 + 0.77 * d;
			c2 = x + 0.23 * d;
			d = w * (x - c3) / (1 + c3 * c3);
			x = c3 + 0.77 * d;
			c3 = x + 0.23 * d;
			d = w * (x - c4);
			x = c4 + 0.77 * d;
			c4 = x + 0.23 * d;
			c5 += 0.85 * (c4 - c5);

			*p1++ = g1 * c4;
		}
	} while (len);

	_c1 = c1;
	_c2 = c2;
	_c3 = c3;
	_c4 = c4;
	_c5 = c5;
	_w = w;
	_r = r;
}

static int _ = MoogLPF::register_class("http://github.com/blablack/ams-lv2/mooglpf");

