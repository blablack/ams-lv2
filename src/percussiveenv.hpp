#ifndef PERCUSSIVEENV_H
#define PERCUSSIVEENV_H

using namespace lvtk;

class PercussiveEnv: public Plugin<PercussiveEnv>
{
	public:
		PercussiveEnv(double rate);
		void run(uint32_t nframes);

	private:
		float e;
		bool trigger, triggered;
		int noteOnOfs;

		double m_rate;
};

#endif
