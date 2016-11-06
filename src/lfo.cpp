#include <lvtk-1/lvtk/plugin.hpp>

#include "lfo.hpp"
#include "lfo_ttl.hpp"

Lfo::Lfo(double rate): Plugin<Lfo>(p_n_ports)
{
	long tm;

	m_rate = rate;
	wave_period = rate / (16.0 * 5);

	trigger = false;
	si = 0;
	old_si = 0;
	sa = -1;
	old_sa = 0;
	t = 0;
	old_t = 0;
	r = 0;
	old_r = 0;
	old_sh = 0;
	sh = 0;
	state = 0;
	dt = 4.0 / wave_period;

	tm = time(NULL) % 1000000;
	srand(abs(tm - 10000 * (tm % 100)));
}

void Lfo::run(uint32_t nframes)
{
	int l2, k, len, l2_out;
	double ldsi, ldsa, ldt, ldr, ldsh, dt0, dsa;

	len = nframes;
	l2 = -1;
	l2_out = 0;
	do
	{
		k = (len > 24) ? 16 : len;
		l2 += k;

		wave_period = m_rate / (16.0 * *p(p_freq));
		dsa = 2.0 / wave_period;
		dt0 = 4.0 / wave_period;

		if (!trigger && (p(p_reset)[l2] > 0.5))
		{
			trigger = true;
			t = 0;
			state = 0;
			dt = dt0;
			r = -1;
			si = 0;
			sa = 0;
		}
		if (trigger && (p(p_reset)[l2] < 0.5))
		{
			trigger = false;
		}

		if (t >= 1.0)
		{
			state = 1;
			dt = -dt0;
		}
		else if (t <= -1.0)
		{
			state = 3;
			dt = dt0;
		}
		else if ((state == 1) && (t < 0))
		{
			state = 2;
			r = 1;
			sh = 2.0 * (double)rand() / (double)RAND_MAX - 1.0;
		}
		else if ((state == 3) && (t > 0))
		{
			state = 0;
			r = -1;
			sh = 2.0 * (double)rand() / (double)RAND_MAX - 1.0;
			sa = -1;
		}

		si = (state < 2) ? t * (2.0 - t) : t * (2.0 + t);
		sa += dsa;
		t += dt;

		if (state == 1 || state == 2)
			dt = -dt0;
		else
			dt = dt0;

		len -= k;
		ldsi = (si - old_si) / (double)k;
		ldsa = (sa - old_sa) / (double)k;
		ldsh = (sh - old_sh) / (double)k;
		ldt = (t - old_t) / (double)k;
		ldr = (r - old_r) / (double)k;
		while (k--)
		{
			old_si += ldsi;
			old_sa += ldsa;
			old_sh += ldsh;
			old_t += ldt;
			old_r += ldr;

			p(p_outSine)[l2_out] = old_si;
			p(p_outTriangle)[l2_out] = old_t;
			p(p_outSawUp)[l2_out] = old_sa;
			p(p_outSawDown)[l2_out] = -old_sa;
			p(p_outRectangle)[l2_out] = -old_r;
			p(p_outSampleHold)[l2_out] = old_sh;

			l2_out++;
		}
	}
	while(len);
}

static int _ = Lfo::register_class("http://github.com/blablack/ams-lv2/lfo");
