#ifndef STEREOMIXER_4CH_H
#define STEREOMIXER_4CH_H

using namespace lvtk;

class StereoMixer4Ch : public Plugin<StereoMixer4Ch>
{
	public:
		StereoMixer4Ch(double rate);
		void run(uint32_t nframes);
};

#endif
