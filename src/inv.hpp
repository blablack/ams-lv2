#ifndef INV_H
#define INV_H

using namespace lvtk;

class Inv: public Plugin<Inv>
{
	public:
		Inv(double rate);
		void run(uint32_t nframes);
};

#endif
