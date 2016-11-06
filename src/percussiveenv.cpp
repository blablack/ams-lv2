#include <lvtk-1/lvtk/plugin.hpp>

#include "percussiveenv.hpp"
#include "percussiveenv_ttl.hpp"

#define ENVELOPE_RESPONSE  256

PercussiveEnv::PercussiveEnv(double rate): Plugin<PercussiveEnv>(p_n_ports)
{
	trigger = false;
	triggered = false;
	noteOnOfs = 0;
	e = 0;

	m_rate = rate;
}

void PercussiveEnv::run(uint32_t nframes)
{
	int status;
	float tscale, de_attack, de_decay;
	float a, dl, dc, h;
	int idl, idla, idlah, idlahdc;

	tscale = *p(p_timeScale) * (float) m_rate;
	de_attack = (*p(p_attack) > 0) ? 1.0 / (*p(p_attack) * tscale) : 0;
	de_decay = (*p(p_decay) > 0) ? 1.0 / (*p(p_decay) * tscale) : 0;
	a = tscale * *p(p_attack);
	dl = tscale * *p(p_delay);
	idl = (int) dl;
	h = tscale * *p(p_hold);
	dc = tscale * *p(p_decay);
	idla = (int) (dl + a);
	idlah = idla + (int) h;
	if (idlah == idla)
	{
		++idlah;
	}

	idlahdc = idlah + (int) dc;
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		if (!trigger && (p(p_trigger)[l2] > 0.5))
		{
			trigger = true;
			triggered = true;
			//noteOnOfs = 0;
			if (e > 0)
				noteOnOfs = (de_attack > 0) ? (int)(e / de_attack) : 0;
			else
				noteOnOfs = 0;
		}
		else if (trigger && (p(p_trigger)[l2] < 0.5))
		{
			trigger = false;
		}

		if (triggered)
		{
			status = 1;
			if (noteOnOfs >= idl)
				status = 2;
			if (noteOnOfs >= idla)
				status = 3;
			if (noteOnOfs >= idlah)
				status = 4;
			if (noteOnOfs >= idlahdc)
				status = 5;
			switch (status)
			{
				case 1:
					e = 0;
					break;
				case 2:
					e += de_attack;
					break;
				case 3:
					e = 1.0;
					break;
				case 4:
					e -= de_decay;
					break;
				case 5:
					e = 0;
					triggered = false;
					break;
			}
			if (e < 0)
				e = 0;

			p(p_out)[l2] = e;
			p(p_invOut)[l2] = -e;
			noteOnOfs++;
		}
		else
		{
			p(p_out)[l2] = 0;
			p(p_invOut)[l2] = 0;
		}
	}
}

static int _ = PercussiveEnv::register_class("http://github.com/blablack/ams-lv2/percussiveenv");

