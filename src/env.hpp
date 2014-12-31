#ifndef ENV_H
#define ENV_H

using namespace lvtk;

class Env: public Plugin<Env>
{
	public:
		Env(double rate);
		void run(uint32_t nframes);

	private:
		float e_noteOff, de;
		double m_rate;

		float e;
		bool gate, retrigger;
		int noteOnOfs;
};

#endif
