#ifndef LFO2_FREQ_H
#define LFO2_FREQ_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "lfo2_freq_ttl.hpp"

using namespace lvtk;

enum WaveFormType
{
	SINUS, TRIANGLE, SAWTOOTHUP, SAWTOOTHDOWN, RECTANGLE, SAMPLEANDHOLD
};

class Lfo2Freq: public Plugin<Lfo2Freq>
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
		Lfo2Freq(double rate);
		void run(uint32_t nframes);
};

#endif
