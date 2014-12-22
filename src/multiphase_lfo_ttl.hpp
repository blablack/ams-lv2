#ifndef ams_lv__multiphase_lfo_ttl_hpp
#define ams_lv__multiphase_lfo_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/multiphase_lfo> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/multiphase_lfo";

enum p_port_enum {
  p_freq,
  p_gainSaw,
  p_gainTriangle,
  p_sawMode,
  p_sawOut_0,
  p_sawOut_45,
  p_sawOut_90,
  p_sawOut_135,
  p_sawOut_180,
  p_sawOut_225,
  p_sawOut_270,
  p_sawOut_315,
  p_triOut_0,
  p_triOut_45,
  p_triOut_90,
  p_triOut_135,
  p_triOut_180,
  p_triOut_225,
  p_triOut_270,
  p_triOut_315,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0.01, 20, 0.1, 0, 0, 0 }, 
  { 0.01, 5, 1, 0, 0, 0 }, 
  { 0.01, 5, 1, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__multiphase_lfo_ttl_hpp */
