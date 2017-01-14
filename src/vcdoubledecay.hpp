#ifndef VCDOUBLEDECAY_H
#define VCDOUBLEDECAY_H

#include "synthdata.hpp"

using namespace lvtk;

class VCDoubleDecay: public Plugin<VCDoubleDecay>
{
	public:
		VCDoubleDecay(double rate);
		void run(uint32_t nframes);

	private:
		const SynthData *synthdata;

		float e, e2, old_e, old_e2, s, old_s;
		int state;
		bool noteActive, gate, retrigger;

		double m_rate;
};

#endif
