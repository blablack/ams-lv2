#ifndef LFO2_TEMPO_H
#define LFO2_TEMPO_H

using namespace lvtk;

enum WaveFormType
{
	SINUS,
	TRIANGLE,
	SAWTOOTHUP,
	SAWTOOTHDOWN,
	RECTANGLE,
	SAMPLEANDHOLD
};

class Lfo2Tempo: public Plugin<Lfo2Tempo>
{
	public:
		Lfo2Tempo(double rate);
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

		int waveForm;

		double m_rate;
};

#endif
