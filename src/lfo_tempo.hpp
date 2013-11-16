#ifndef LFO_TEMPO_H
#define LFO_TEMPO_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "lfo_tempo_ttl.hpp"

using namespace lvtk;

enum WaveFormType
{
	SINUS, TRIANGLE, SAWTOOTHUP, SAWTOOTHDOWN, RECTANGLE, SAMPLEANDHOLD
};

class LfoTempo: public Plugin<LfoTempo>
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

		int waveForm;

		double m_rate;

	public:
		LfoTempo(double rate);
		void run(uint32_t nframes);
};

#endif
