#ifndef VCALIN_H
#define VCALIN_H

using namespace lvtk;

class VcaLin: public Plugin<VcaLin>
{
	public:
		VcaLin(double rate);
		void run(uint32_t nframes);
};

#endif
