#ifndef AMPLITUDE_H
#define AMPLITUDE_H

using namespace lvtk;

class Amplitude: public Plugin<Amplitude>
{
	public:
		Amplitude(double rate);
		void run(uint32_t nframes);
};

#endif
