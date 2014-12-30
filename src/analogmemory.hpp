#ifndef ANALOGMEMORY_H
#define ANALOGMEMORY_H

using namespace lvtk;

class AnalogMemory: public Plugin<AnalogMemory>
{
	public:
		AnalogMemory(double rate);
		~AnalogMemory();
		void run(uint32_t nframes);

	private:
		int offset;
		float *buf;
		int lastwrite;
};

#endif
