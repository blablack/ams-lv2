#ifndef ams_lv__vcdelay_ttl_hpp
#define ams_lv__vcdelay_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcdelay> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcdelay";

enum p_port_enum {
  p_input,
  p_vcdelay,
  p_delay,
  p_vmod,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 10, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__vcdelay_ttl_hpp */
