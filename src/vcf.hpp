#ifndef VCF_H
#define VCF_H

#include "synthdata.hpp"

using namespace lvtk;

enum vcfTypeEnum
{
	VCF_LR,
	VCF_LPF,
	VCF_HPF,
	VCF_BPF_I,
	VCF_BPF_II,
	VCF_NF,
	VCF_MOOG1,
	VCF_MOOG2
};

class Vcf : public Plugin<Vcf>
{
	public:
		Vcf(double rate);
		void run(uint32_t nframes);

	private:
		int vcfTypeUsed;

		double in[5], buf[5];

		float dBgain;
		float freq_const;
		float fInvertRandMax ;
		float pi2_rate,inv2_rate;
		float freq_tune, gain_linfm, qr, moog_f, revMoog, moog2times;
		double b_noise;

		const SynthData *synthdata;

		void initBuf();
};

#endif
