#ifndef ams_lv__vcf_ttl_hpp
#define ams_lv__vcf_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcf> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcf";

enum p_port_enum {
  p_in,
  p_freqPort,
  p_expFM,
  p_linFM,
  p_resonancePort,
  p_vcfType,
  p_inputGain,
  p_freq,
  p_expFMGain,
  p_linFMGain,
  p_resonance,
  p_resonanceGain,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 7, 0, 0, 0, 0 }, 
  { 0, 10, 1, 0, 0, 0 }, 
  { 0, 10, 5, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0.01, 1, 0.8, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__vcf_ttl_hpp */
