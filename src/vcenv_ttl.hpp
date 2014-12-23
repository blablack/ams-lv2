#ifndef ams_lv__vcenv_ttl_hpp
#define ams_lv__vcenv_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcenv> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcenv";

enum p_port_enum {
  p_gate,
  p_retrigger,
  p_attack,
  p_decay,
  p_sustain,
  p_release,
  p_attackOffset,
  p_decayOffset,
  p_sustainOffset,
  p_releaseOffset,
  p_attackGain,
  p_decayGain,
  p_sustainGain,
  p_releaseGain,
  p_timescale,
  p_decayreleasemode,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -8, 8, 0, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { -8, 8, 1, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__vcenv_ttl_hpp */
