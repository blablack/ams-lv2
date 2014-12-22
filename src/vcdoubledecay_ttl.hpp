#ifndef ams_lv__vcdoubledecay_ttl_hpp
#define ams_lv__vcdoubledecay_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcdoubledecay> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcdoubledecay";

enum p_port_enum {
  p_gate,
  p_retrigger,
  p_attack,
  p_decay,
  p_sustain,
  p_release,
  p_ratio,
  p_attackOffset,
  p_decayOffset,
  p_sustainOffset,
  p_ratioOffset,
  p_releaseOffset,
  p_attackGain,
  p_decayGain,
  p_sustainGain,
  p_ratioGain,
  p_releaseGain,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0.5, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__vcdoubledecay_ttl_hpp */
