#ifndef VCDELAY_H
#define VCDELAY_H

using namespace lvtk;

class VCDelay: public Plugin<VCDelay>
{
	public:
		VCDelay(double rate);
		~VCDelay();
		void run(uint32_t nframes);

	private:
		int read_ofs;
		float *buf;
};

#endif
