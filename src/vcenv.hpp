#ifndef VCENV_H
#define VCENV_H

using namespace lvtk;

class VCEnv: public Plugin<VCEnv>
{
	public:
		VCEnv(double rate);
		void run(uint32_t nframes);
};

#endif
