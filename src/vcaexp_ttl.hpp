#ifndef ams_lv__vcaexp_ttl_hpp
#define ams_lv__vcaexp_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/vcaexp> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/vcaexp";

enum p_port_enum {
  p_gain1Data,
  p_gain2Data,
  p_in1Data,
  p_in2Data,
  p_gain1,
  p_gain2,
  p_in1,
  p_in2,
  p_outputLevel,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__vcaexp_ttl_hpp */
