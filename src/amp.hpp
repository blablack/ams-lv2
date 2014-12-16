#ifndef AMP_H
#define AMP_H

using namespace lvtk;

class Amp: public Plugin<Amp>
{
	public:
		Amp(double rate);
		void run(uint32_t nframes);
};

#endif
