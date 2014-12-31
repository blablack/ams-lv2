#include <lvtk-1/lvtk/plugin.hpp>

#include "bitgrinder.hpp"
#include "bitgrinder_ttl.hpp"

BitGrinder::BitGrinder(double rate): Plugin<BitGrinder>(p_n_ports)
{
	m_rate = rate;
}

void BitGrinder::run(uint32_t nframes)
{
	unsigned int l2;

	for (l2 = 0; l2 < nframes; l2++) {
		samplecounter += (*p(p_fractionaldatarate) + (p(p_rateVC)[l2] * *p(p_ratevcmodulation)))
						 * m_rate;

		//    Part 1: sample slower than the data rate, if desired.
		if (samplecounter < 0) samplecounter = 0;
		if ( samplecounter > m_rate)
		{
			samplecounter -= m_rate;
			sval = p(p_in)[l2];   // sval is a static
		}

		// Part 2: decrease the bit resolution; assume a -1/+1 range
		// for our bit assignment (note that this means a signal of
		// +/- 2volts will get 2 bits even when set to 1 bit.
		unsigned int temp;
		int activebits;
		activebits = *p(p_bitspervolt) + (*p(p_bitsvcmodulation) * p(p_bitsVC)[l2]);
		temp = (int ((sval) * 16777216.0 )) + 1073741824 ;   // * 2^24 + 2^30
		// Now we have 24 bit precision integer, biased up by 2^30
		// shift it down and back, to clear those low order bits.
		temp = temp >> (26 - (int(activebits)));
		temp = temp << (26 - (int(activebits)));
		p(p_out)[l2] = ((float (temp) - 1073741824.0 ) / 16777216.0)
						  + 1.0 / (float (activebits));
	}
}

static int _ = BitGrinder::register_class("http://github.com/blablack/ams-lv2/bitgrinder");

