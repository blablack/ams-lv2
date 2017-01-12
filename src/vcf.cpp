#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "vcf.hpp"
#include "vcf_ttl.hpp"

#define MIN_FREQ                         20
#define MAX_FREQ                      20000
#define MAX_FREQ2                     22000

Vcf::Vcf(double rate): Plugin<Vcf>(p_n_ports)
{
	synthdata = &SynthData::instance();

	vcfTypeUsed = -1;

	dBgain = 3.0;
	freq_const = 2.85f / 20000.0f;
	fInvertRandMax= 1.0f/(float)RAND_MAX ;
	b_noise = 19.1919191919191919191919191919191919191919;
	pi2_rate = 2.0f * M_PI / rate; // how often changes the rate? I guess once on init, or?
	inv2_rate = 2.0 / (double)rate;// this double seems unnecessary
}

void Vcf::initBuf()
{
	for(int i=0 ; i<5 ; i++) {
		in[i]=0;
		buf[i]=0;
	}
}

void Vcf::run(uint32_t nframes)
{
	unsigned int l2;
	double t1, t2, fa, fb, q0, f, q, p_, iv_sin, iv_cos, iv_alpha, a0, a1, a2, b0, b1, b2;

	if ( vcfTypeUsed != (int)(*p(p_vcfType)) ) {
		initBuf();
		vcfTypeUsed = (int)(*p(p_vcfType));
	}

	switch (vcfTypeUsed) {
		case VCF_LR:
		{
			double b_noiseout;
			int i_noise;
			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = freq_const * (synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
								  + gain_linfm * p(p_linFM)[l2]);
				if (f < 0.0) f = 0.0;
				else if (f > 0.99) f = 0.99;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				fa = 1.0 - f;
				fb = q * (1.0 + (1.0 / fa));
				// generate dither (?) noise
				b_noise = b_noise * b_noise;
				i_noise = (int)b_noise;
				b_noise = b_noise - i_noise;
				b_noiseout = b_noise - 1.5;// was 0.5
				b_noise = b_noise + 19.0;

				buf[0] = fa * buf[0] + f * (*p(p_inputGain) * p(p_in)[l2] + fb * (buf[0] - buf[1]) + 0.00001 * b_noiseout);// ((float)rand() * fInvertRandMax - 1.0f));
				buf[1] = fa * buf[1] + f * buf[0];
				p(p_out)[l2] = buf[1];
			}

			break;
		}
		case VCF_LPF:
		{
			double temp;

			q0 = *p(p_resonance);

			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ) f = MAX_FREQ;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				iv_sin = sin(pi2_rate * f);
				iv_cos = cos(pi2_rate * f);
				iv_alpha = iv_sin/(64.0 * q);
				b0 = (1.0 - iv_cos) * 0.5;
				b1 = 1.0 - iv_cos;
				b2 = b0;
				a0 = 1.0 + iv_alpha;
				a1 = -2.0 * iv_cos;
				a2 = 1.0 - iv_alpha;
				temp = 1.0 / a0 * (b0 * *p(p_inputGain) * p(p_in)[l2] + b1 * buf[0] + b2 * buf[1]
					   - a1 * buf[2] - a2 * buf[3]);
				p(p_out)[l2]=temp;
				buf[1] = buf[0];
				buf[0] = *p(p_inputGain) * p(p_in)[l2];
				buf[3] = buf[2];
				buf[2] = temp;//p(p_out)[l2];
			}

			break;
		}
		case VCF_HPF:
		{
			double temp;

			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ) f = MAX_FREQ;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				iv_sin = sin(pi2_rate * f);
				iv_cos = cos(pi2_rate * f);
				iv_alpha = iv_sin/(64.0 * q);
				b0 = (1.0 + iv_cos) * 0.5;
				b1 = - 1.0 - iv_cos;
				b2 = b0;
				a0 = 1.0 + iv_alpha;
				a1 = -2.0 * iv_cos;
				a2 = 1.0 - iv_alpha;
				temp = 1.0 / a0 * (*p(p_inputGain) * b0 * p(p_in)[l2] + b1 * buf[0] + b2 * buf[1]
					   - a1 * buf[2] - a2 * buf[3]);
				p(p_out)[l2]=temp;
				buf[1] = buf[0];
				buf[0] = *p(p_inputGain) * p(p_in)[l2];
				buf[3] = buf[2];
				buf[2] = temp;//p(p_out)[l2];
			}

			break;
		}
		case VCF_BPF_I:
		{
			double temp;

			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ) f = MAX_FREQ;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				iv_sin = sin(pi2_rate * f);
				iv_cos = cos(pi2_rate * f);
				iv_alpha = iv_sin/(64.0 * q);
				b0 = q * iv_alpha;
				b1 = 0.0;
				b2 = -q * iv_alpha;
				a0 = 1.0 + iv_alpha;
				a1 = -2.0 * iv_cos;
				a2 = 1.0 - iv_alpha;

				temp = 1.0 / a0 * (*p(p_inputGain) * b0 * p(p_in)[l2] + b1 * buf[0] + b2 * buf[1]
					   - a1 * buf[2] - a2 * buf[3]);
				p(p_out)[l2]=temp;
				buf[1] = buf[0];
				buf[0] = *p(p_inputGain) * p(p_in)[l2];
				buf[3] = buf[2];
				buf[2] = temp;//p(p_out)[l2];
			}

			break;
		}
		case VCF_BPF_II:
		{
			double temp;
			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ) f = MAX_FREQ;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				iv_sin = sin(pi2_rate * f);
				iv_cos = cos(pi2_rate * f);
				iv_alpha = iv_sin/(64.0 * q);
				b0 = iv_alpha;
				b1 = 0.0;
				b2 = -iv_alpha;
				a0 = 1.0 + iv_alpha;
				a1 = -2.0 * iv_cos;
				a2 = 1.0 - iv_alpha;
				temp = 1.0 / a0 * (*p(p_inputGain) * b0 * p(p_in)[l2] + b1 * buf[0] + b2 * buf[1]
					   - a1 * buf[2] - a2 * buf[3]);
				p(p_out)[l2] = temp;
				buf[1] = buf[0];
				buf[0] = *p(p_inputGain) * p(p_in)[l2];
				buf[3] = buf[2];
				buf[2] = temp;//p(p_out)[l2];
			}

			break;
		}
		case VCF_NF:
		{
			double temp;
			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ) f = MAX_FREQ;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				iv_sin = sin(pi2_rate * f);
				iv_cos = cos(pi2_rate * f);
				iv_alpha = iv_sin/(64.0 * q);
				b0 = 1.0;
				b1 = -2.0 * iv_cos;
				b2 = 1.0;
				a0 = 1.0 + iv_alpha;
				a1 = -2.0 * iv_cos;
				a2 = 1.0 - iv_alpha;

				temp = 1.0 / a0 * (*p(p_inputGain) * b0 * p(p_in)[l2] + b1 * buf[0] + b2 * buf[1]
					   - a1 * buf[2] - a2 * buf[3]);
				p(p_out)[l2] = temp;// conversion
				buf[1] = buf[0];
				buf[0] = *p(p_inputGain) * p(p_in)[l2];
				buf[3] = buf[2];
				buf[2] = temp;//p(p_out)[l2];
			}

			break;
		}
		case VCF_MOOG1:
		{// Timo Tossavainen version
			double b_noiseout;
			int i_noise;
			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ2) f = MAX_FREQ2;
				q = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (q < 0.01) q = 0.01;
				else if (q > 1.0) q = 1.0;
				fa = inv2_rate * f;
				moog_f = fa * 1.16f;
				revMoog = 1.0f - moog_f;
				moog2times= moog_f * moog_f;
				fb = 4.1 * q * (1.0 - 0.15 * moog2times);
				// generate dither (?) noise
				b_noise = b_noise * b_noise;
				i_noise = (int)b_noise;
				b_noise = b_noise - i_noise;

				b_noiseout = b_noise - 1.5; // was - 0.5 now with - 1.0

				b_noise = b_noise + 19.0;
				in[0] = *p(p_inputGain) * p(p_in)[l2] + 0.000001 * b_noiseout;//((float)rand() * fInvertRandMax - 1.0);
				in[0] -= fb * buf[4];
				in[0] *=0.35013 * (moog2times * moog2times);
				buf[1] = in[0] + 0.3 * in[1] + revMoog * buf[1];
				in[1] = in[0];
				buf[2] = buf[1] + 0.3 * in[2] + revMoog * buf[2];
				in[2] = buf[1];
				buf[3] = buf[2] + 0.3 * in[3] + revMoog * buf[3];
				in[3] = buf[2];
				buf[4] = buf[3] + 0.3 * in[4] + revMoog * buf[4];
				in[4] = buf[3];
				p(p_out)[l2] = buf[4];
			}

			break;
		}
		case VCF_MOOG2:                       // Paul Kellet version
		{
			double b_noiseout;
			int i_noise;

			q0 = *p(p_resonance);
			freq_tune = 5.0313842f + *p(p_freq);
			gain_linfm = 1000.0f * *p(p_linFMGain);

			for (l2 = 0; l2 < nframes; ++l2) {
				f = synthdata->exp2_table(freq_tune + p(p_freqPort)[l2] + *p(p_expFMGain) * p(p_expFM)[l2])
					+ gain_linfm * p(p_linFM)[l2];
				if (f < MIN_FREQ) f = MIN_FREQ;
				else if (f > MAX_FREQ2) f = MAX_FREQ2;
				qr = q0 + *p(p_resonanceGain) * p(p_resonancePort)[l2];
				if (qr < 0.01) qr = 0.01;
				else if (qr > 1.0) qr = 1.0;
				fb = inv2_rate * f;
				q = 1.0 - fb;
				p_ = fb + 0.8 * fb * q;
				fa = p_ + p_ - 1.0;
				q = qr * (1.0 + 0.5 * q * (1.0 - q + 5.6 * q * q));
				// generate dither (?) noise
				b_noise = b_noise * b_noise;
				i_noise = (int)b_noise;
				b_noise = b_noise - i_noise;

				b_noiseout = b_noise - 1.5;// was 0.5

				b_noise = b_noise + 19.0;

				in[0] = *p(p_inputGain) * p(p_in)[l2] + 0.000001 * b_noiseout;//* ((float)rand() * fInvertRandMax - 1.0);
				in[0] -= q * buf[4];
				if (in[0] < -1.0) in[0] = -1.0;
				if (in[0] > 1.0) in[0] = 1.0;
				t1 = buf[1];
				buf[1] = (in[0] + buf[0]) * p_ - buf[1] * fa;
				t2 = buf[2];
				buf[2] = (buf[1] + t1) * p_ - buf[2] * fa;
				t1 = buf[3];
				buf[3] = (buf[2] + t2) * p_ - buf[3] * fa;
				buf[4] = (buf[3] + t1) * p_ - buf[4] * fa;
				buf[4] -= buf[4] * buf[4] * buf[4] * 0.166667;
				buf[0] = in[0];
				p(p_out)[l2] = buf[4];
			}

			break;
		}
	}
}

static int _ = Vcf::register_class("http://github.com/blablack/ams-lv2/vcf");

