#ifndef SYNTHDATA_H
#define SYNTHDATA_H

#include <stdlib.h>

#define EXP2_DEPTH 15
#define EXP2_BUF_LEN (1<<EXP2_DEPTH)

//#define WAVE_PERIOD             65536
#define WAVE_PERIOD             262144
#define EXP_TABLE_LEN           32768
#define MAX_ANALOGUE_DRIVER_OUT     6

class SynthData
{
	public:
		float wave_sine[WAVE_PERIOD];
		float wave_saw[WAVE_PERIOD];
		float wave_saw2[WAVE_PERIOD];
		float wave_rect[WAVE_PERIOD];
		float wave_tri[WAVE_PERIOD];
		float exp_data[EXP_TABLE_LEN];
		float exp2_data[EXP2_BUF_LEN];

		SynthData();

		float exp_table(float x);
		float exp2_table(float);
};

//extern SynthData *synthdata;

#endif

