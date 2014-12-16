#ifndef STEREOMIXER_2CH_H
#define STEREOMIXER_2CH_H

using namespace lvtk;

class StereoMixer2Ch : public Plugin<StereoMixer2Ch>
{
	public:
		StereoMixer2Ch(double rate);
		void run(uint32_t nframes);
};

#endif
