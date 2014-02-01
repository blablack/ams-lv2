#ifndef LFO_H
#define LFO_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "lfo_ttl.hpp"

using namespace lvtk;

class Lfo: public Plugin<Lfo>
{
	private:
		double si, old_si;
		double sa, old_sa;
		double t, old_t;
		double r, old_r;
		double sh, old_sh;
		int state;
		double dt, wave_period;
		bool trigger;

		double m_rate;

	public:
		Lfo(double rate);
		void run(uint32_t nframes);
};

#endif
