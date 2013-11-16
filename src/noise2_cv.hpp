#ifndef NOISE2_H
#define NOISE2_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "noise2_cv_ttl.hpp"

using namespace lvtk;

enum Noises
{
	WHITE, RAND, PINK
};

class Noise2CV: public Plugin<Noise2CV>
{
	private:
		int NoiseType;
		unsigned int count;
		float buf[3], r;
		float randmax;

	public:
		Noise2CV(double rate);
		void run(uint32_t nframes);
};

#endif
