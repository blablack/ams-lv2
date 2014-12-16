#ifndef MIXER_4CH_H
#define MIXER_4CH_H

using namespace lvtk;

class Mixer4Ch : public Plugin<Mixer4Ch>
{
	public:
		Mixer4Ch(double rate);
		void run(uint32_t nframes);
};

#endif
