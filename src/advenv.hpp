#ifndef ADVENV_H
#define ADVENV_H

using namespace lvtk;

class AdvEnv: public Plugin<AdvEnv>
{
	public:
		AdvEnv(double rate);
		void run(uint32_t nframes);

	private:
		float attack[8], sustain, release[5];
		float e_noteOff, de, de_release;

		double m_rate;

		float e;
		float timeScale;
		bool noteActive, gate, retrigger;
		int noteOnOfs;
		int noteOffOfs;
		float *gateData, *retriggerData;
};

#endif
