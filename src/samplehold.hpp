#ifndef SAMPLEHOLD_H
#define SAMPLEHOLD_H

using namespace lvtk;

class SampleHold: public Plugin<SampleHold>
{
	public:
		SampleHold(double rate);
		void run(uint32_t nframes);

	private:
		float triggerLevel, sample;
		bool gate;
};

#endif
