#ifndef RINGMODULATOR_H
#define RINGMODULATOR_H

using namespace lvtk;

class RingModulator: public Plugin<RingModulator>
{
	private:
		float gain;
	public:
		RingModulator(double rate);
		void run(uint32_t nframes);
};

#endif
