#include <lvtk-1/lvtk/plugin.hpp>

#include "analogmemory.hpp"
#include "analogmemory_ttl.hpp"

#define MAX_ANALOGMEMORY_2N_FRAMES 20

AnalogMemory::AnalogMemory(double rate): Plugin<AnalogMemory> (p_n_ports)
{
	int cells = 1<<MAX_ANALOGMEMORY_2N_FRAMES;

	buf = (float *)malloc( cells * sizeof(float));
	memset(buf, 0, cells * sizeof(float));

	lastwrite = 0;
	offset = 0;
}

AnalogMemory::~AnalogMemory()
{
	free(buf);
}

void AnalogMemory::run(uint32_t nframes)
{
	unsigned int l2;
	int cells;
	int i;

	cells = 1 << (int)*p(p_n);

	int addrmode = (int)*p(p_write_addressing_mode);

	for (l2 = 0; l2 < nframes; l2++) {
		// First we write, then we read.
		// Calculate addresses, scaled -1 to +1 to match LFOs
		offset = (int) (cells * ((((float) p(p_read_addr)[l2]) + 1.0)/ 2.0));
		if (offset >= cells)
			offset = cells - 1;
		if (offset < 0) offset = 0;
		if (p(p_write_ena)[l2] >= *p(p_write_tresh))
		{
			if (addrmode == 0)  // direct linear
				buf[offset] = p(p_input_cv)[l2];
			if (addrmode == 1)   // upward only, no fill.
				if (offset > lastwrite)
				{
					buf [offset] = p(p_input_cv)[l2];
				};
			if (addrmode == 2)   // Upward fill.
			{
				if ( offset > lastwrite)  // Simpler case- lw < wo
				{
					for (i = lastwrite+1; i <= offset; i++)
						buf[i] = p(p_input_cv)[l2];
				}
			};
			if (addrmode == 3)   // downward only, no fill.
				if (offset < lastwrite)
				{
					buf [offset] = p(p_input_cv)[l2];
				};
			if (addrmode == 4)   // Downward, fill.
				if ( offset < lastwrite)  // Simpler case- lw < wo
				{
					for (i = lastwrite-1; i >= offset; i--)
						buf[i] = p(p_input_cv)[l2];
				};
		};
		lastwrite = offset;

		// then read..
		offset = (int) (cells * ((((float)p(p_write_addr)[l2]) + 1.0)/ 2.0));
		if (offset >= cells)
			offset = cells - 1;
		if (offset < 0) offset = 0;
		p(p_out_cv)[l2] = buf[offset];
	}
}

static int _ = AnalogMemory::register_class("http://github.com/blablack/ams-lv2/analogmemory");

