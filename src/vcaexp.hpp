#ifndef VCAEXP_AUDIO_H
#define VCAEXP_AUDIO_H

#include "synthdata.hpp"

using namespace lvtk;

class VcaExp: public Plugin<VcaExp>
{
	private:
		SynthData *synthdata;

	public:
		VcaExp(double rate);
		void run(uint32_t nframes);
};

#endif
