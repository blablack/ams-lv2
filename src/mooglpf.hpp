#ifndef MOOGLPF_H
#define MOOGLPF_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "mooglpf_ttl.hpp"

using namespace lvtk;

class MoogLPF: public Plugin<MoogLPF>
{
	private:
	  float _c1, _c2, _c3, _c4, _c5, _w, _r;
	  double m_rate;

	  float exp2ap (float x);
	public:
		MoogLPF(double rate);
		void run(uint32_t nframes);
};

#endif
