#ifndef ams_lv__vcpanning_ttl_hpp
#define ams_lv__vcpanning_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcpanning> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcpanning";

enum p_port_enum {
  p_in,
  p_panCV,
  p_panOffset,
  p_panGain,
  p_panningMode,
  p_out1,
  p_out2,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 2, 0, 0, 0, 0 }, 
  { 0, 4, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__vcpanning_ttl_hpp */
