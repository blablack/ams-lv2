#ifndef HZTOVC_H
#define HZTOVC_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "hztovc_ttl.hpp"

using namespace lvtk;

class HzToVc: public Plugin<HzToVc>
{
	private:
		int octave;
		double m_rate;
		float m_eighth, m_log2inv;

	public:
		HzToVc(double rate);
		void run(uint32_t nframes);
};

#endif
