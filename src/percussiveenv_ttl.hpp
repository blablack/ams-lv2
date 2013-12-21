#ifndef ams_lv__percussiveenv_ttl_hpp
#define ams_lv__percussiveenv_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/percussiveenv> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/percussiveenv";

enum p_port_enum {
  p_trigger,
  p_attack,
  p_decay,
  p_delay,
  p_hold,
  p_timeScale,
  p_out,
  p_invOut,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.1, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0.02, 0, 0, 0 }, 
  { 1, 10, 0.1, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -1, 0, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__percussiveenv_ttl_hpp */
