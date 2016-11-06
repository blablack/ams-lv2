#include <lvtk-1/lvtk/plugin.hpp>

#include "vcdelay.hpp"
#include "vcdelay_ttl.hpp"

#define MAX_DELAY_FRAMES  32768

VCDelay::VCDelay(double rate): Plugin<VCDelay> (p_n_ports)
{
	buf = (float *) malloc(MAX_DELAY_FRAMES * sizeof(float));
	memset(buf, 0, MAX_DELAY_FRAMES * sizeof(float));

	read_ofs = 0;
}

VCDelay::~VCDelay()
{
	free(buf);
}

void VCDelay::run(uint32_t nframes)
{
	int ofs, delay_frames, vc_delay_frames;

	delay_frames = (int)((float)((MAX_DELAY_FRAMES/2) - 3) * *p(p_delay) / 10.0);
	for (unsigned int l2 = 0; l2 < nframes; l2++) {
		buf[read_ofs] = p(p_input)[l2];
		vc_delay_frames = delay_frames * (1 + p(p_vcdelay)[l2] * *p(p_vmod));
		ofs = read_ofs - vc_delay_frames;
		ofs = ofs % MAX_DELAY_FRAMES;
		if (ofs < 0) ofs += MAX_DELAY_FRAMES;
		p(p_output)[l2] = buf[ofs];
		read_ofs++;
		if (read_ofs >= MAX_DELAY_FRAMES) read_ofs = 0;
	}
}

static int _ = VCDelay::register_class("http://github.com/blablack/ams-lv2/vcdelay");

