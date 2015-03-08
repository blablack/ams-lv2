#include <lvtk-1/lvtk/plugin.hpp>

#include "haas.hpp"
#include "haas_ttl.hpp"

//#define MAX_DELAY_FRAMES  16384

Haas::Haas(double rate): Plugin<Haas> (p_n_ports)
{
	m_rate = rate;
	m_buffer_size = m_rate / 1000 * 50;

	buf_l = (float *) malloc(m_buffer_size * sizeof(float));
	buf_r = (float *) malloc(m_buffer_size * sizeof(float));
	memset(buf_l, 0, m_buffer_size * sizeof(float));
	memset(buf_r, 0, m_buffer_size * sizeof(float));

	read_ofs = 0;
}

Haas::~Haas()
{
	free(buf_l);
	free(buf_r);
}

void Haas::run(uint32_t nframes)
{
	int ofs, delay_frames;

	m_wet = *p(p_dry_wet) / 100;
	m_dry = 1 - m_wet;

	int p_delay = *p(p_delay);
	if (p_delay<5)
		p_delay = 5;
	else if (p_delay>40)
		p_delay = 40;

	delay_frames = m_rate / 1000 * p_delay;
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		buf_l[read_ofs] = p(p_input_l)[l2];
		buf_r[read_ofs] = p(p_input_r)[l2];
		ofs = read_ofs - delay_frames;
		if (ofs < 0)
			ofs = m_buffer_size + ofs;
		p(p_output_l)[l2] = p(p_input_l)[l2] * m_dry + buf_r[ofs] * m_wet;
		p(p_output_r)[l2] = p(p_input_r)[l2] * m_dry + buf_l[ofs] * m_wet;

		read_ofs++;
		if (read_ofs >= m_buffer_size)
			read_ofs = 0;
	}
}

static int _ = Haas::register_class("http://github.com/blablack/ams-lv2/haas");

