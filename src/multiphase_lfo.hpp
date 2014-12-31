#ifndef MULTIPHASE_LFO_H
#define MULTIPHASE_LFO_H

using namespace lvtk;

class MultiphaseLfo: public Plugin<MultiphaseLfo>
{
	public:
		MultiphaseLfo(double rate);
		void run(uint32_t nframes);

	private:
		double m_rate;
		double tri, saw, d_tri, d_saw;
		int state;
};

#endif
