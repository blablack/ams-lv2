#ifndef SLEW_H
#define SLEW_H

using namespace lvtk;

class Slew: public Plugin<Slew>
{
	public:
		Slew(double rate);
		void run(uint32_t nframes);

	private:
		float lastData;
		double m_rate;
		float *inData;
};

#endif
