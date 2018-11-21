#include <math.h>

#include "synthdata.hpp"

union uf
{
		struct
		{
				unsigned int mant :23;
				unsigned int exp :8;
				unsigned int sign :1;
		} p;
		float f;
		unsigned u;
};

SynthData::SynthData()
{
	int l1, l2;
	double dphi, phi, dy, dyd;
	int decaytime;

	decaytime = (int) ((float) WAVE_PERIOD / 16.0);

	dphi = 2.0 * M_PI / WAVE_PERIOD;
	phi = 0;
	for (l1 = 0; l1 < WAVE_PERIOD; l1++)
	{
		wave_sine[l1] = sin(phi);
		phi += dphi;
	}
	for (l1 = 0; l1 < EXP_TABLE_LEN; l1++)
		exp_data[l1] = exp(l1 / 1000.0 - 16.0);
	{
		unsigned u = 0;
		for (float f = 0; f < 1; f += 1.0 / EXP2_BUF_LEN)
		{
			union uf e;
			e.f = exp2f(f);
			e.p.exp = 0;
			exp2_data[u++] = e.f;
		}
	}
	dy = 2.0 / (float) (WAVE_PERIOD - decaytime);
	dyd = 2.0 / decaytime;
	l2 = 0;
	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_saw[l2++] = (float) l1 * dy;

	for (l1 = 0; l1 < decaytime; l1++)
		wave_saw[l2++] = 1.0 - (float) l1 * dyd;

	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_saw[l2++] = -1.0 + (float) l1 * dy;

	l2 = WAVE_PERIOD - 1;
	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_saw2[l2--] = (float) l1 * dy;

	for (l1 = 0; l1 < decaytime; l1++)
		wave_saw2[l2--] = 1.0 - (float) l1 * dyd;

	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_saw2[l2--] = -1.0 + (float) l1 * dy;

	l2 = 0;
	dyd = 4.0 / decaytime;
	for (l1 = 0; l1 < decaytime >> 2; l1++)
		wave_rect[l2++] = (float) l1 * dyd;

	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_rect[l2++] = 1.0;

	for (l1 = 0; l1 < decaytime >> 1; l1++)
		wave_rect[l2++] = 1.0 - (float) l1 * dyd;

	for (l1 = 0; l1 < (WAVE_PERIOD - decaytime) >> 1; l1++)
		wave_rect[l2++] = -1.0;

	for (l1 = 0; l1 < decaytime >> 2; l1++)
		wave_rect[l2++] = -1.0 + (float) l1 * dyd;

	dy = 4.0 / (float) WAVE_PERIOD;
	for (l1 = 0; l1 < (WAVE_PERIOD >> 2); l1++)
		wave_tri[l1] = (float) l1 * dy;

	for (l1 = (WAVE_PERIOD >> 2); l1 < (WAVE_PERIOD >> 1) + (WAVE_PERIOD >> 2); l1++)
		wave_tri[l1] = 1.0 - (float) (l1 - (WAVE_PERIOD >> 2)) * dy;

	for (l1 = (WAVE_PERIOD >> 1) + (WAVE_PERIOD >> 2); l1 < WAVE_PERIOD; l1++)
		wave_tri[l1] = -1.0 + (float) (l1 - (WAVE_PERIOD >> 1) - (WAVE_PERIOD >> 2)) * dy;
}

float SynthData::exp_table(float x) const
{
	int index;

	index = (int) ((x + 16.0) * 1000.0);
	if (index >= EXP_TABLE_LEN)
		index = EXP_TABLE_LEN - 1;
	else if (index < 0)
		index = 0;
	return (exp_data[index]);
}

float SynthData::exp2_table(float f) const
{
	if (f < -16)
		return 0;

	union uf uf, uexp2;
	uf.f = f + 17;

	unsigned exp = (uf.u >> 23) - 0x7f;
	unsigned mant = uf.p.mant;

	unsigned e = exp;
	exp = 1 << e;
	exp += mant >> (23 - e);

	mant <<= e;
	mant &= (1 << 23) - 1;
	mant >>= 23 - EXP2_DEPTH;

	uexp2.f = exp2_data[mant];
	uexp2.u |= (exp + 0x7F - 17) << 23;

	return uexp2.f;
}

SynthData SynthData::single_instance_;
