#ifndef ams_lv__advenv_ttl_hpp
#define ams_lv__advenv_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/advenv> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/advenv";

enum p_port_enum {
  p_gate,
  p_retrigger,
  p_timeScale,
  p_sustain,
  p_delay,
  p_attackTime1,
  p_attackTime2,
  p_attackTime3,
  p_attackTime4,
  p_attackLevel1,
  p_attackLevel2,
  p_attackLevel3,
  p_releaseTime1,
  p_releaseTime2,
  p_releaseTime3,
  p_releaseLevel1,
  p_releaseLevel2,
  p_out,
  p_invOut,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0.1, 10, 1, 0, 0, 0 }, 
  { 0, 1, 0.7, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.1, 0, 0, 0 }, 
  { 0, 1, 0.5, 0, 0, 0 }, 
  { 0, 1, 1, 0, 0, 0 }, 
  { 0, 1, 0.9, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.5, 0, 0, 0 }, 
  { 0, 1, 0.2, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -1, 0, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__advenv_ttl_hpp */
