#ifndef VCALIN_CV_H
#define VCALIN_CV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcalin_cv_ttl.hpp"

using namespace lvtk;

class VcaLinCV: public Plugin<VcaLinCV>
{
	public:
		VcaLinCV(double rate);
		void run(uint32_t nframes);
};

#endif
