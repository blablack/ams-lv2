#include <lvtk-1/lvtk/plugin.hpp>

#include "fftvocoder.hpp"
#include "fftvocoder_ttl.hpp"

FFTVocoder::FFTVocoder(double rate): Plugin<FFTVocoder>(p_n_ports)
{
	whichwin = 0;

	modbuf = 0;
	carrbuf = 0;
	window = 0;
	modmap = 0;
	armodmap = 0;

	planmodforward = 0;
	planmodbackward = 0;
	plancarrforward = 0;
	plancarrbackward = 0;

	carrinforward = 0;
	carrinbackward = 0;
	carroutforward = 0;
	carroutbackward = 0;
	modinforward = 0;
	modinbackward = 0;
	modoutforward = 0;
	modoutbackward = 0;

	p_firstRound = true;
}

FFTVocoder::~FFTVocoder()
{
	free (modbuf);
	free (carrbuf);
	free (window);
	free (modmap);
	free (armodmap);

	fftw_destroy_plan (planmodforward);
	fftw_destroy_plan (planmodbackward);
	fftw_destroy_plan (plancarrforward);
	fftw_destroy_plan (plancarrbackward);

	fftw_free(carrinforward);
	fftw_free(carrinbackward);
	fftw_free(carroutforward);
	fftw_free(carroutbackward);
	fftw_free(modinforward);
	fftw_free(modinbackward);
	fftw_free(modoutforward);
	fftw_free(modoutbackward);
}

void FFTVocoder::run(uint32_t nframes)
{
	if( p_firstRound ) {
		initial( nframes );
		p_firstRound = false;
	}
	unsigned int l2;  // l2 indexes along the cycle

	//       *** Insuring continuity across FFTs  ***
	//    One problem with shifting, etc. is to insure
	//    that the output is continuous in position
	//    across FFT frames.  If *all* you do is forward and
	//    reverse FFT, then there's no problem.  However, if you
	//    do any manipulation of the FFT-format data, then you can
	//    (and usually do) get steps in output at the frame boundaries
	//    when you transform back.  This is audible as a series of
	//    signal-dependent pulses at the frame rate (about 48 Hz for
	//    a cycle size of 1024 and a 48 KHz sample rate. )
	//
	//    The hack fix we use here is to keep a buffer of the last
	//    cyclesize samples we saw, and append them together, then
	//    pick a chunk with level- and gradient-matching to use as
	//    our output.  This is turned on and off by the "Dynamic
	//    splicing" checkbox.
	//
	//    To keep the CPU load down, we stay with a power-of-two FFT
	//    size.  That is, 2 * cyclesize; compared to something not a
	//    power of two, say 1280, 2048 is actually a lot faster to
	//    execute and so what looks like more work is actually
	//    considerably less work.


	//   Did the user change the FFT windowing function?
	int myFFTWindowFunc = (int)(*p(p_fftwindowfunction));
	if (myFFTWindowFunc != whichwin) {
		whichwin = myFFTWindowFunc;
		for (l2 = 0; l2 < (unsigned int) fftsize; l2++)
			window[l2] = windowcurve (whichwin, fftsize, l2, 0.25);
	}

	//  copy the modulator input into inbuf

	for (l2 = 0; l2 < fftsize - nframes; l2++) {
		modbuf[l2] = modbuf  [l2 + nframes];
	}
	for (l2 = 0; l2 < nframes; l2++) {
		modbuf[l2 + fftsize - nframes ] = p(p_modulator)[l2];
	}

	//    Copy the input buffer to modinforward
	for (l2 = 0; l2 < (unsigned int)fftsize ; l2++) {
		modinforward[l2] = modbuf[l2] * window[l2];
	}

	//   and forward FFT the modulator
	fftw_execute (planmodforward);

	//    copy the FFT of the modulator to modinbackward.
	for (l2 = 0; l2 < (unsigned int)fftsize; l2++)
		modinbackward[l2] = modoutforward[l2];

	//     Send the FFT of the modulator to the output for giggles
	//     and get an approximation of the first harmonic too.
	float firstharmonicval;
	int firstharmonicindex;
	firstharmonicval = 0.0;
	firstharmonicindex = 1.0;
	for (l2 = 1; l2 < (unsigned int) nframes; l2++) {
		p(p_modulatorfft)[l2] = logf(fabs (creal (modoutforward[l2])) + 1.0);
		if (p(p_modulatorfft)[l2] > firstharmonicval) {
			firstharmonicindex = l2;
			firstharmonicval  = p(p_modulatorfft)[l2] ;
		}
	};
	p(p_modulatorfft)[0] = -10.0;
	for (l2 = 0; l2 < (unsigned int) nframes; l2++) {
		p(p_mod1stH)[l2] = log2 (firstharmonicindex);
	};

	//   intermediate frequency-domain munging of modulator
	//   Frequency (additive, Bode-style) shifting first
	for (l2 = 0; l2 < (unsigned int)fftsize; l2++)
		modinbackward[l2] = 0;
	int lclfrq;
	for (l2 = 0; l2 < (unsigned int)fftsize/2; l2++) {
		//   positive frequencies (first half) of the FFT result
		lclfrq = l2 + (int)*p(p_freq_bode_shift) + *p(p_vcfreqshift) * p(p_freqshift)[0];
		lclfrq = lclfrq > 0 ? lclfrq : 0;
		lclfrq = lclfrq < ((fftsize/2)-1) ? lclfrq : (fftsize/2)-1;
		modinbackward[ lclfrq ] = modoutforward [l2];
		//   Negative frequencies (second half of the fft result)
		modinbackward[fftsize - lclfrq] = modoutforward [ fftsize - l2];
	}

	//    Pitchshifting (multiplicative, harmonic-retaining) shifting.
	//    Note that we reuse the modoutforward as working space
	for (l2 = 0; l2 < (unsigned int) fftsize; l2++) {
		modoutforward[l2] = modinbackward[l2];
	};
	for (l2 = 0; l2 < (unsigned int)fftsize; l2++)
		modinbackward[l2] = 0;

	float psmod, psfactor;
	psmod = (*p(p_pitchshift_octaves) + *p(p_vcpitchshift) * p(p_pitchshift)[0]);
	psfactor = pow (2.0, psmod);
	for (l2 = 0; l2 < (unsigned int)fftsize/2; l2++) {
		//   positive frequencies (first half) of the FFT result
		lclfrq = l2 * psfactor;
		lclfrq = lclfrq > 0 ? lclfrq : 0;
		lclfrq = lclfrq < ((fftsize/2)-1) ? lclfrq : (fftsize/2)-1;
		//   Old way to pitch shift: just move the bucket.  But this puts
		//   nulls wherever the energy is split between two buckets with
		//   a 180 degree phase difference.
		if (*p(p_rthetamodulator) == 0) {
			modinbackward[lclfrq] += modoutforward [l2];
			modinbackward[fftsize - lclfrq] += modoutforward [ fftsize - l2];
		}
		else
		{
			//
			//   Better way: move freq. bin, multiply angle by octave motion.
			//
			modinbackward[lclfrq] +=
					cabs (modoutforward [l2])
					* cexp (I * ( carg (modoutforward [l2])
								  + (l2 * *p(p_phaseshift) * psfactor)));
			modinbackward[fftsize - lclfrq] +=
					cabs (modoutforward [ fftsize - l2])
					* cexp (I * ( carg (modoutforward [ fftsize - l2])
							+ (l2 * *p(p_phaseshift) * psfactor)));
		};
	}
	//     The munged modulator is now in "inbackward"
	//     so inverse-FFT it and output it as altered modulator.
	fftw_execute (planmodbackward);

	//   renormalize the time-domain modulator output
	for (l2 = 0; l2 < (unsigned)fftsize; l2++) {
		modoutbackward [l2] = modoutbackward[l2] / float (fftsize) ;
		modoutbackward [l2] = modoutbackward[l2] / window[l2];
	}

	unsigned int i;
	float residual;
	int clomatch_index;


	//     Splicing the new output to the results
	if (*p(p_dynamicsplicing) == 0.0)
	{
		//   output it as the altered modulator.
		for (l2 = 0; l2 < nframes; l2++) {
			p(p_alteredmod)[l2] = creal ( modoutbackward [l2 +
								  fftsize/2 -
								  nframes/2 ]);
		}
		clomatch_index = fftsize - nframes;
	}
	else
	{
		//   find where in our altered modulator output where a "close match"
		//   exists to our previous output value, then output one
		//   cyclesize worth starting there.  Note that since we start at the
		//   start, we get almost a complete fftsize worth of range to
		//   choose from.
		float clov_sofar;
		float tval, dtval;
		int searchstart;
		float spliceval, dspliceval;
		searchstart = fftsize/2 - nframes;
		if (searchstart < 1) searchstart = 1;
		clomatch_index = searchstart;
		spliceval = p(p_alteredmod)[nframes - 1];
		dspliceval = spliceval - p(p_alteredmod)[nframes - 2];
		clov_sofar= fabs(creal(modoutbackward[clomatch_index])-spliceval );
		for (l2 = searchstart;
			 l2 < (searchstart + nframes);
			 l2++)
		{
			tval = creal (modoutbackward[l2]);
			dtval = tval - creal (modoutbackward [l2-1]);
			if (
					((fabs (tval - spliceval )) < clov_sofar )
					&& ((dtval * dspliceval ) >= 0)
					)
			{
				clov_sofar= fabs (tval - spliceval );
				clomatch_index = l2;
				// fprintf (stderr, "%f %d ", clov_sofar, clomatch_index);
			}
		};
		//  fprintf (stderr, "%d %f %f ",
		//      clomatch_index, clov_sofar, clodv_sofar);

		//   What's our residual error, so that we can splice this
		//   with minimal "click"?
		residual = + spliceval - creal( modoutbackward[clomatch_index]);

		//  Move our wave, with the best match so far established, to
		//   the output buffer area.
		for (l2 = 0; l2 < nframes; l2++) {
			p(p_alteredmod)[l2] = creal ( modoutbackward [ clomatch_index + l2])
					+ ((1.0 - (float(l2) / float(nframes))) * residual);
		};

	};

	// fprintf (stderr, "%f %d  \n", residual, clomatch_index);

	//     Now it's time to do the carrier.
	//
	for (l2 = 0; l2 < fftsize - nframes; l2++) {
		carrbuf [l2] = carrbuf [l2 + nframes];
	}
	for (l2 = 0; l2 < nframes; l2++) {
		carrbuf [l2 + fftsize - nframes] = p(p_carrier)[l2];
	}

	for (l2 = 0; l2 <  unsigned (fftsize); l2++) {
		carrinforward [l2] = carrbuf [l2] * window[l2];
	}

	fftw_execute (plancarrforward);

	for (l2 = 0; l2 < (unsigned) fftsize; l2++) {
		carrinbackward[l2] = carroutforward[l2];
	};

	//   carroutforward now has the carrier,

	//      modoutforward now has the modulator.
	//   Group the modulator into channels, and multipy the channels
	//   over the carrier.

	int localchannels;
	localchannels = *p(p_bins_channel) + *p(p_vcbins_channels) * p(p_channels)[0];
	if (localchannels < 1) localchannels = 1;
	if (localchannels > fftsize - 1) localchannels = fftsize - 1;
	for (l2 = 0; l2 < (unsigned) fftsize; l2++) {
		modmap[l2] = 0;
		//       initial conditions...
		if (l2 == 0)
			for (i = 0; i < *p(p_bins_channel); i++)
				modmap[l2] += cabs (modoutforward[l2 + i]);
		else
			modmap [l2] = modmap[l2 - 1];

		//    add the heads, subtract the tails
		i = l2 + *p(p_bins_channel);
		if (l2 < (unsigned)fftsize - 2)
			modmap[l2] += cabs( modoutforward [i] );
		i = l2 - *p(p_bins_channel);
		if (l2 >= *p(p_bins_channel))
			modmap[l2] -= cabs( modoutforward [i] );
	}

	//   Normalize the modmap
	for (l2 = 0; l2 < (unsigned) fftsize; l2++)
		modmap[l2] = modmap[l2] / localchannels;

	//   Do attack/release
	for (l2 = 0; l2 < (unsigned) fftsize; l2++) {
		if (modmap [l2] > armodmap[l2])
			armodmap [l2] += (1 - *p(p_attacktime)) * (modmap[l2] - armodmap[l2]);
		if (modmap [l2] < armodmap[l2])
			armodmap [l2] += (1 - *p(p_releasetime)) * (modmap[l2] - armodmap[l2]);
	}

	//   multiply the carrier by the modulation map.
	for (l2 = 0; l2 < (unsigned) fftsize; l2++) {
		carrinbackward[l2] = carroutforward[l2] * armodmap[l2];
	}

	//   reverse transform to final output, and renormalize by 1/fftsize.
	fftw_execute (plancarrbackward);

	int offset;
	for (l2 = 0; l2 < nframes; l2++) {
		offset = l2 + (fftsize/2) - (nframes / 2);
		p(p_vocoderout)[l2]=
				(creal(carroutbackward[offset]/window[offset])) / (fftsize * 100);
	};
}

void FFTVocoder::initial(uint32_t nframes)
{
	unsigned int l2;

	fftsize = nframes * 4;

	whichwin = 0;
	window = (float *) malloc (sizeof (float) * fftsize);
	for (l2 = 0; l2 < (unsigned int) fftsize; l2++)
		window[l2] = windowcurve (whichwin, fftsize, l2, 0.25);

	modbuf = (float *)malloc( fftsize * sizeof(float));
	memset( modbuf, 0, fftsize * sizeof(float));

	carrbuf = (float *)malloc( fftsize * sizeof(float));
	memset( carrbuf, 0, fftsize * sizeof(float));

	modmap = (float *) malloc (sizeof (float) * fftsize);
	armodmap = (float *) malloc (sizeof (float) * fftsize);

	//  FFTW setup stuff
	carrinforward = fftw_alloc_complex (fftsize);
	carrinbackward = fftw_alloc_complex (fftsize);
	carroutforward = fftw_alloc_complex (fftsize);
	carroutbackward = fftw_alloc_complex (fftsize);
	modinforward = fftw_alloc_complex (fftsize);
	modinbackward = fftw_alloc_complex (fftsize);
	modoutforward = fftw_alloc_complex (fftsize);
	modoutbackward = fftw_alloc_complex (fftsize);

	fftw_set_timelimit (0.1);

	planmodforward = fftw_plan_dft_1d (fftsize, modinforward, modoutforward, FFTW_FORWARD, FFTW_MEASURE);
	planmodbackward = fftw_plan_dft_1d (fftsize, modinbackward, modoutbackward, FFTW_BACKWARD, FFTW_MEASURE);
	plancarrforward = fftw_plan_dft_1d (fftsize, carrinforward, carroutforward, FFTW_FORWARD, FFTW_MEASURE);
	plancarrbackward = fftw_plan_dft_1d (fftsize, carrinbackward, carroutbackward, FFTW_BACKWARD, FFTW_MEASURE);
}

//   Window function - One way to make the FFT behave
//   and give more continuous results over edge steps.

float FFTVocoder::windowcurve (int windowfunc, int len, int elem, float alpha)
{
	float out;
	out = 1.0;
	switch (windowfunc)
	{
		case 0:
			//  Rectangular window
			out = 1.0;
			break;
		case 1:
			//  Trapezoidal window.
			out = 1.0;
			if (elem < alpha * len)
			{
				out = elem / (alpha * len);
			}
			if ( (len - elem) > len - (alpha * len) )
			{
				out = (len - elem) / (alpha * len) ;
			}
			break;
		case 2:
			//  Hann window (raised cosine)
			out = 0.5 * (1.0 - cos (3.14159 * 2 * elem / (len - 1)));
			break;
		case 3:
			//  Hamming window
			out = 0.54 - 0.46 * cos (3.14159 * 2 * elem / (len - 1));
			break;
		case 4:
			//  Tukey window
			out = 1;
			if ( elem <= (alpha * len / 2) )
				out = (1 + cos (3.14159 * (((2 * elem) / (alpha * len))
										   - 1))) / 2;
			if (elem >= (len * (1 - alpha/2)))
				out = (1 + cos (3.14159 * (((2 * elem) / (alpha * len))
										   - (2 * alpha)
										   + 1))) / 2;
			break;
		case 5:
			//  Blackman-Nutall (least spillover)
			out =
					0.3635819
					- 0.4891775 * cos (2 * 3.14159 * elem / (len - 1))
					+ 0.1365995 * cos (4 * 3.14159 * elem / (len - 1))
					- 0.0106411 * cos (6 * 3.14159 * elem / (len - 1));
			break;
	}
	return (out);
}

static int _ = FFTVocoder::register_class("http://github.com/blablack/ams-lv2/fftvocoder");

