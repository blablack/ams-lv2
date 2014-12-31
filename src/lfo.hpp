#ifndef LFO_H
#define LFO_H

using namespace lvtk;

class Lfo: public Plugin<Lfo>
{
	public:
		Lfo(double rate);
		void run(uint32_t nframes);

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
};

#endif
