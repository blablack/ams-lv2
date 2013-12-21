#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "hztovc.hpp"

using namespace lvtk;

HzToVc::HzToVc(double rate)
:Plugin<HzToVc>(p_n_ports)
 {
	m_rate = rate;
	m_eighth = 1.0f/8.0f;
	m_log2inv = 1.0f/logf(2.0);
 }

void HzToVc::run(uint32_t nframes)
{
	unsigned int l2;
	float offset;

	float *inData = p(p_input);
	octave = floor(*p(p_octaveOffset));

	offset = octave + 5.0313842;
	for (l2 = 0; l2 < nframes; l2++)
	{
		//p(p_output)[l2] = exp(M_LN2 * (offset + inData[l2]));
		p(p_output)[l2] = logf((p(p_input)[l2]) * m_eighth) * m_log2inv - offset;
	}
}

static int _ = HzToVc::register_class("http://github.com/blablack/ams-lv2/hztovc");

