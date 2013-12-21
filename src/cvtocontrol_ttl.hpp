#ifndef ams_lv__cvtocontrol_ttl_hpp
#define ams_lv__cvtocontrol_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/cvtocontrol> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/cvtocontrol";

enum p_port_enum {
  p_input,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__cvtocontrol_ttl_hpp */
