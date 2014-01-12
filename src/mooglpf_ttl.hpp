#ifndef ams_lv__mooglpf_ttl_hpp
#define ams_lv__mooglpf_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/mooglpf> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/mooglpf";

enum p_port_enum {
  p_inputGain,
  p_frequency,
  p_expFMGain,
  p_resonance,
  p_resonanceGain,
  p_outputGain,
  p_portInput,
  p_portFrequency,
  p_portExpFM,
  p_portResonance,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -15, 15, 0, 0, 0, 0 }, 
  { -6, 6, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -15, 15, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__mooglpf_ttl_hpp */
