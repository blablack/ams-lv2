#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "noise2_cv.hpp"

Noise2CV::Noise2CV(double rate)
: Plugin<Noise2CV>(p_n_ports)
  {
	long t;

	count = 0;
	NoiseType = WHITE;
	randmax = 2.0f / (float)RAND_MAX;

	r = 0;
	for (int l2 = 0; l2 < 3; ++l2)
	{
		buf[l2] = 0;
	}
	t = time(NULL) % 1000000;
	srand(abs(t - 10000 * (t % 100)));
  }

void Noise2CV::run(uint32_t nframes)
{
	NoiseType = floor(*p(p_noiseType));

	switch (NoiseType)
	{
		case WHITE:
		{
			for (unsigned int l2 = 0; l2 < nframes; ++l2)
			{
				p(p_out)[l2] = rand() * randmax - 1.0f;
			}
		}
		break;
		case RAND:
		{
			unsigned int random_rate = (unsigned int)(5000.0 * (double)*p(p_rate) + 100.0);
			for (unsigned int l2 = 0; l2 < nframes; ++l2)
			{
				count++;
				if (count > random_rate)
				{
					count = 0;
					r = *p(p_level) * rand() * randmax - 1.0f;
				}
				p(p_out)[l2] = r;
			}
		}
		break;
		case PINK:
		{
			for (unsigned int l2 = 0; l2 < nframes; ++l2)
			{
				float white_noise = rand() * randmax - 1.0f;

				buf[0] = 0.99765f * buf[0] + white_noise * 0.099046f;
				buf[1] = 0.963f * buf[1] + white_noise * 0.2965164f;
				buf[2] = 0.57f * buf[2] + white_noise * 1.0526913f;

				p(p_out)[l2] = buf[0] + buf[1] + buf[2] + white_noise * 0.1848f;
			}
		}
		break;
	}
}

static int _ = Noise2CV::register_class("http://github.com/blablack/ams.lv2/noise2_cv");

