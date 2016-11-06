#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "hztovc.hpp"
#include "hztovc_ttl.hpp"

HzToVc::HzToVc(double rate): Plugin<HzToVc>(p_n_ports)
{
	m_eighth = 1.0f/8.0f;
	m_log2inv = 1.0f/logf(2.0);
}

void HzToVc::run(uint32_t nframes)
{
	float offset = (int)(*p(p_octaveOffset)) + 5.0313842;
	float freq = (int)(*p(p_input));
	if (freq < 1 )
		freq = 1;

	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_output)[l2] = logf(freq * m_eighth) * m_log2inv - offset;
}

static int _ = HzToVc::register_class("http://github.com/blablack/ams-lv2/hztovc");

