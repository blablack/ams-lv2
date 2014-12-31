#ifndef VCTOHZ_H
#define VCTOHZ_H

using namespace lvtk;

class VcToHz: public Plugin<VcToHz>
{
	public:
		VcToHz(double rate);
		void run(uint32_t nframes);

	private:
		int convMode, octave;
		double m_rate;
};

#endif
