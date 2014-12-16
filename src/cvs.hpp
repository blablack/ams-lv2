#ifndef CVS_H
#define CVS_H

using namespace lvtk;

class Cvs: public Plugin<Cvs>
{
	public:
		Cvs(double rate);
		void run(uint32_t nframes);
};

#endif
