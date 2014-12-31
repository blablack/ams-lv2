#ifndef ams_lv__hysteresis_ttl_hpp
#define ams_lv__hysteresis_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/hysteresis> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/hysteresis";

enum p_port_enum {
  p_in,
  p_center,
  p_overlap,
  p_lowSlope,
  p_highSlope,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -2, 2, 0, 0, 0, 0 }, 
  { 0, 4, 0, 0, 0, 0 }, 
  { -5, 5, 0, 0, 0, 0 }, 
  { -5, 5, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__hysteresis_ttl_hpp */
