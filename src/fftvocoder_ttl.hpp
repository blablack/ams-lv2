#ifndef ams_lv__fftvocoder_ttl_hpp
#define ams_lv__fftvocoder_ttl_hpp


#ifndef PEG_STRUCT
#define PEG_STRUCT
typedef struct {
  float min;
  float max;
  float default_value;
  char toggled;
  char integer;
  char logarithmic;
} peg_data_t;
#endif

/* <http://github.com/blablack/ams-lv2/fftvocoder> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/fftvocoder";

enum p_port_enum {
  p_modulator,
  p_pitchshift,
  p_freqshift,
  p_channels,
  p_carrier,
  p_bins_channel,
  p_vcbins_channels,
  p_attacktime,
  p_releasetime,
  p_pitchshift_octaves,
  p_vcpitchshift,
  p_freq_bode_shift,
  p_vcfreqshift,
  p_phaseshift,
  p_fftwindowfunction,
  p_dynamicsplicing,
  p_rthetamodulator,
  p_alteredmod,
  p_vocoderout,
  p_modulatorfft,
  p_mod1stH,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 1, 999, 16, 0, 0, 0 }, 
  { -100, 100, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -3, 3, 0, 0, 0, 0 }, 
  { -5, 5, 0, 0, 0, 0 }, 
  { -999, 999, 0, 0, 0, 0 }, 
  { -500, 500, 0, 0, 0, 0 }, 
  { -6.28, 6.28, 0, 0, 0, 0 }, 
  { 0, 5, 0, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__fftvocoder_ttl_hpp */
