#ifndef CVTOCONTROL_H
#define CVTOCONTROL_H

using namespace lvtk;

class CVToControl: public Plugin<CVToControl>
{
	public:
		CVToControl(double rate);
		void run(uint32_t nframes);
};

#endif
