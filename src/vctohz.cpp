#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vctohz.hpp"
#include "vctohz_ttl.hpp"

VcToHz::VcToHz(double rate): Plugin<VcToHz>(p_n_ports)
{
	m_rate = rate;
}

void VcToHz::run(uint32_t nframes)
{
	float offset;

	float *inData = p(p_input);
	convMode = (int)(*p(p_conversionMode));
	octave = (int)(*p(p_octaveOffset));

	offset = octave + 5.0313842;
	if (convMode == 0)
	{
		for (unsigned int l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = exp(M_LN2 * (offset + inData[l2]));
		}
	}
	else if (convMode == 1)
	{
		for (unsigned int l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = 2.0 * exp(M_LN2 * (offset + inData[l2])) / m_rate;
		}
	}
	else if (convMode == 2)
	{
		for (unsigned int l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = exp(M_LN2 * (offset + inData[l2])) / 20000.0;
		}
	}
}

static int _ = VcToHz::register_class("http://github.com/blablack/ams-lv2/vctohz");

