#include <lvtk-1/lvtk/plugin.hpp>

#include "controltocv.hpp"
#include "controltocv_ttl.hpp"

ControlToCV::ControlToCV(double rate): Plugin<ControlToCV>(p_n_ports)
{
}

void ControlToCV::run(uint32_t nframes)
{
	for (unsigned int l2 = 0; l2 < nframes; l2++)
		p(p_output)[l2] = *p(p_input);
}

static int _ = ControlToCV::register_class("http://github.com/blablack/ams-lv2/controltocv");

