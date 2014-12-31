#ifndef RINGMODULATOR_H
#define RINGMODULATOR_H

using namespace lvtk;

class RingModulator: public Plugin<RingModulator>
{
	public:
		RingModulator(double rate);
		void run(uint32_t nframes);

	private:
		float gain;
};

#endif
