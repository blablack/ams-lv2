#ifndef CONTROLTOCV_H
#define CONTROLTOCV_H

using namespace lvtk;

class ControlToCV: public Plugin<ControlToCV>
{
	public:
		ControlToCV(double rate);
		void run(uint32_t nframes);
};

#endif
