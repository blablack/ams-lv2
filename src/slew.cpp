#include <lvtk-1/lvtk/plugin.hpp>

#include "slew.hpp"
#include "slew_ttl.hpp"

Slew::Slew(double rate): Plugin<Slew>(p_n_ports)
{
	lastData = 0;
	m_rate = rate;
}

void Slew::run(uint32_t nframes)
{
	float ds, slewUp, slewDown;

	inData = p(p_in);

	if (*p(p_timeUp) > 0.0001)
	{
		slewUp = 1.0 / (*p(p_timeUp) * (float)m_rate);
	}
	else
	{
		slewUp = 1.0 / (0.0001 * (float)m_rate);
	}
	if (*p(p_timeDown) > 0.0001)
	{
		slewDown = -1.0 / (*p(p_timeDown) * (float)m_rate);
	}
	else
	{
		slewDown = -1.0 / (0.0001 * (float)m_rate);
	}

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		ds = inData[l2] - lastData;
		if (ds > 0)
		{
			if (ds > slewUp) ds = slewUp;
		}
		else
		{
			if (ds < slewDown) ds = slewDown;
		}
		p(p_out)[l2] = lastData + ds;
		lastData = p(p_out)[l2];
	}
}

static int _ = Slew::register_class("http://github.com/blablack/ams-lv2/slew");

