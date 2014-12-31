#ifndef NOISE2_H
#define NOISE2_H

using namespace lvtk;

enum Noises
{
	WHITE,
	RAND,
	PINK,
	PULSETRAIN
};

class Noise2: public Plugin<Noise2>
{
	public:
		Noise2(double rate);
		void run(uint32_t nframes);

	private:
		int NoiseType;
		unsigned int count;
		float buf[3], r;
		float randmax;
};

#endif
