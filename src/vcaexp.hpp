#ifndef VCAEXP_AUDIO_H
#define VCAEXP_AUDIO_H

#include "synthdata.hpp"

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcaexp_ttl.hpp"

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
