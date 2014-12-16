#ifndef DELAY_H
#define DELAY_H

using namespace lvtk;

class Delay: public Plugin<Delay>
{
	public:
		Delay(double rate);
		~Delay();
		void run(uint32_t nframes);

	private:
		float m_delay;
		int read_ofs;
		float *buf;
};

#endif
