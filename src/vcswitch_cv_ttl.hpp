#ifndef ams_lv__vcswitch_cv_ttl_hpp
#define ams_lv__vcswitch_cv_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcswitch_cv> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcswitch_cv";

enum p_port_enum {
  p_switchlevel,
  p_cv,
  p_in1,
  p_in2,
  p_out1,
  p_out2,
  p_outmix,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 10, 0.5, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__vcswitch_cv_ttl_hpp */
