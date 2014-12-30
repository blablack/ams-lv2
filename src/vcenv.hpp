#ifndef VCENV_H
#define VCENV_H

using namespace lvtk;

class VCEnv: public Plugin<VCEnv>
{
	public:
		VCEnv(double rate);
		void run(uint32_t nframes);

	private:
		double m_rate;

		float e, old_e;
		int state;
		bool noteActive, gate, retrigger;

		//float a0, d0, s0, r0, aGain, dGain, sGain, rGain;
		//int timeScale, decayReleaseMode;
};

#endif
