#ifndef MIXER_8CH_H
#define MIXER_8CH_H

using namespace lvtk;

class Mixer8Ch : public Plugin<Mixer8Ch>
{
	public:
		Mixer8Ch(double rate);
		void run(uint32_t nframes);
};

#endif
