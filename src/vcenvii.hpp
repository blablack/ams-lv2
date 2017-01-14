#ifndef VCENVII_H
#define VCENVII_H

#include "synthdata.hpp"

using namespace lvtk;

class VCEnvII: public Plugin<VCEnvII>
{
	public:
		VCEnvII(double rate);
		void run(uint32_t nframes);

	private:
		const SynthData *synthdata;

		double m_rate;

		float e, old_e;
		int state;
		bool noteActive, gate, retrigger;
};

#endif
