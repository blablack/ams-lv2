#include <lvtk-1/lvtk/plugin.hpp>

#include "lfo2_tempo.hpp"
#include "lfo2_tempo_ttl.hpp"

Lfo2Tempo::Lfo2Tempo(double rate):  Plugin<Lfo2Tempo>(p_n_ports)
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

	waveForm = SINUS;

	tm = time(NULL) % 1000000;
	srand(abs(tm - 10000 * (tm % 100)));
}

void Lfo2Tempo::run(uint32_t nframes)
{
	int l2, k, len, l2_out;
	double ldsi, ldsa, ldt, ldr, ldsh, dt0, dsa;

	waveForm = (int)(*p(p_waveForm));

	double p_multiplierValue = *p(p_tempoMultiplier);

	if(p_multiplierValue <= 0.0078125)
		p_multiplierValue = (0.0078125);
	else if(p_multiplierValue <= 0.015625)
		p_multiplierValue = (0.015625);
	else if(p_multiplierValue <= 0.03125)
		p_multiplierValue = (0.03125);
	else if(p_multiplierValue <= 0.0625)
		p_multiplierValue = (0.0625);
	else if(p_multiplierValue <= 0.125)
		p_multiplierValue = (0.125);
	else if(p_multiplierValue <= 0.25)
		p_multiplierValue = (0.25);
	else if(p_multiplierValue <= 0.5)
		p_multiplierValue = (0.5);
	else if(p_multiplierValue <= 1)
		p_multiplierValue = (1);
	else if(p_multiplierValue <= 2)
		p_multiplierValue = (2);
	else if(p_multiplierValue <= 4)
		p_multiplierValue = (4);
	else if(p_multiplierValue <= 8)
		p_multiplierValue = (8);
	else if(p_multiplierValue <= 16)
		p_multiplierValue = (16);
	else if(p_multiplierValue <= 32)
		p_multiplierValue = (32);
	else if(p_multiplierValue <= 64)
		p_multiplierValue = (64);
	else if(p_multiplierValue > 64)
		p_multiplierValue = (128);

	len = nframes;
	l2 = -1;
	l2_out = 0;
	do
	{
		k = (len > 24) ? 16 : len;
		l2 += k;

		wave_period = m_rate / (16.0 * *p(p_tempo) / 60 * p_multiplierValue);
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

			switch (waveForm)
			{
				case SINUS:
					p(p_output)[l2_out] = old_si;
					break;
				case TRIANGLE:
					p(p_output)[l2_out] = old_t;
					break;
				case SAWTOOTHUP:
					p(p_output)[l2_out] = old_sa;
					break;
				case SAWTOOTHDOWN:
					p(p_output)[l2_out] = -old_sa;
					break;
				case RECTANGLE:
					p(p_output)[l2_out] = -old_r;
					break;
				case SAMPLEANDHOLD:
					p(p_output)[l2_out] = old_sh;
					break;
			}

			l2_out++;
		}
	}
	while(len);
}

static int _ = Lfo2Tempo::register_class("http://github.com/blablack/ams-lv2/lfo2_tempo");
