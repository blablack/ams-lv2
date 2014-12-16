#ifndef ENV_H
#define ENV_H

using namespace lvtk;

class Env: public Plugin<Env>
{
	private:
		float e_noteOff, de;
		double m_rate;

		float e;
		bool gate, retrigger;
		int noteOnOfs;

	public:
		Env(double rate);
		void run(uint32_t nframes);
};

#endif
