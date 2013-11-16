#ifndef VCAEXP_CV_H
#define VCAEXP_CV_H

#include "synthdata.hpp"

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcaexp_cv_ttl.hpp"

using namespace lvtk;

class VcaExpCV: public Plugin<VcaExpCV>
{
	private:
		SynthData *synthdata;

	public:
		VcaExpCV(double rate);
		void run(uint32_t nframes);
};

#endif
