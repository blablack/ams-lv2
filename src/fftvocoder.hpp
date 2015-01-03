#ifndef FFTVOCODER_H
#define FFTVOCODER_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex.h>
#include<time.h>
#include<fftw3.h>

class FFTVocoder : public lvtk::Plugin<FFTVocoder>
{
	public:
		FFTVocoder(double rate);
		~FFTVocoder();
		void run(uint32_t nframes);

	private:
		int whichwin;
		bool p_firstRound;
		int fftsize;

		// window for FFT; computed once and reused.
		float *window;

		// the previous time-based samples, for overlapping
		float *modbuf, *carrbuf;

		fftw_plan planmodforward, planmodbackward,
		plancarrforward, plancarrbackward;

		fftw_complex *carrinforward, *carroutforward,
		*carrinbackward, *carroutbackward,
		*modinforward, *modoutforward,
		*modinbackward, *modoutbackward;

		// modulation map - result of FFT + channelize of modulator
		float *modmap;
		// modmap with attack/release filtering.
		float *armodmap;

		void initial(uint32_t nframes);
		float windowcurve (int windowfunc, int len, int elem, float alpha );
};

#endif
