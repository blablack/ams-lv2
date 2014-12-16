#include <lvtk-1/lvtk/plugin.hpp>

#include "delay.hpp"
#include "delay_ttl.hpp"

#define MAX_DELAY_FRAMES  16384

Delay::Delay(double rate): Plugin<Delay> (p_n_ports)
{
	m_delay = 0;

	buf = (float *) malloc(MAX_DELAY_FRAMES * sizeof(float));
	memset(buf, 0, MAX_DELAY_FRAMES * sizeof(float));

	read_ofs = 0;
}

Delay::~Delay()
{
	free(buf);
}

void Delay::run(uint32_t nframes)
{
	m_delay = *p(p_delay);

	int ofs, delay_frames;

	delay_frames = (int) ((float) (MAX_DELAY_FRAMES - 3) * m_delay / 10.0);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		buf[read_ofs] =  p(p_input)[l2];
		ofs = read_ofs - delay_frames;
		if (ofs < 0)
			ofs += MAX_DELAY_FRAMES;
		p(p_output)[l2] = buf[ofs];

		read_ofs++;
		if (read_ofs >= MAX_DELAY_FRAMES)
			read_ofs = 0;
	}
}

static int _ = Delay::register_class("http://github.com/blablack/ams-lv2/delay");

