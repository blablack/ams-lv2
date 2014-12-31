#ifndef BITGRINDER_H
#define BITGRINDER_H

using namespace lvtk;

class BitGrinder: public Plugin<BitGrinder>
{
	public:
		BitGrinder(double rate);
		void run(uint32_t nframes);

	private:
		double m_rate;
		float sval;
		float samplecounter;
};

#endif
