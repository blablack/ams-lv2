#ifndef ams_lv__vcorgan___ttl_hpp
#define ams_lv__vcorgan___ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcorgan_6> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcorgan_6";

enum p_port_enum {
  p_freq,
  p_expFM,
  p_linFM,
  p_octave,
  p_tune,
  p_expFMGain,
  p_linFMGain,
  p_volume1,
  p_volume2,
  p_volume3,
  p_volume4,
  p_volume5,
  p_volume6,
  p_vco1_waveForm,
  p_vco1_octave,
  p_vco1_tune,
  p_vco1_harmonic,
  p_vco1_subharmonic,
  p_vco1_phi0,
  p_vco2_waveForm,
  p_vco2_octave,
  p_vco2_tune,
  p_vco2_harmonic,
  p_vco2_subharmonic,
  p_vco2_phi0,
  p_vco3_waveForm,
  p_vco3_octave,
  p_vco3_tune,
  p_vco3_harmonic,
  p_vco3_subharmonic,
  p_vco3_phi0,
  p_vco4_waveForm,
  p_vco4_octave,
  p_vco4_tune,
  p_vco4_harmonic,
  p_vco4_subharmonic,
  p_vco4_phi0,
  p_vco5_waveForm,
  p_vco5_octave,
  p_vco5_tune,
  p_vco5_harmonic,
  p_vco5_subharmonic,
  p_vco5_phi0,
  p_vco6_waveForm,
  p_vco6_octave,
  p_vco6_tune,
  p_vco6_harmonic,
  p_vco6_subharmonic,
  p_vco6_phi0,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { 0, 6, 0, 0, 0, 0 }, 
  { 0, 6, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 1, 16, 1, 0, 0, 0 }, 
  { 0, 6.283, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__vcorgan___ttl_hpp */
