#ifndef PERCUSSIVEENV_H
#define PERCUSSIVEENV_H

using namespace lvtk;

class PercussiveEnv: public Plugin<PercussiveEnv>
{
	private:
		float e;
		bool trigger, triggered;
		int noteOnOfs;

		double m_rate;

	public:
		PercussiveEnv(double rate);
		void run(uint32_t nframes);
};

#endif
