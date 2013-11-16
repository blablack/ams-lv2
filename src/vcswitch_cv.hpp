#ifndef VCSWITCH_CV_H
#define VCSWITCH_CV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcswitch_cv_ttl.hpp"

using namespace lvtk;

class VCSwitchCV: public Plugin<VCSwitchCV>
{
	private:
		float switchlevel;
	public:
		VCSwitchCV(double rate);
		void run(uint32_t nframes);
};

#endif
