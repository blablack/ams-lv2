#ifndef ams_lv__stereomixer__ch_ttl_hpp
#define ams_lv__stereomixer__ch_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/stereomixer_4ch> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/stereomixer_4ch";

enum p_port_enum {
  p_masterVolume,
  p_in1,
  p_mute1,
  p_solo1,
  p_volume1,
  p_pan1,
  p_in2,
  p_mute2,
  p_solo2,
  p_volume2,
  p_pan2,
  p_in3,
  p_mute3,
  p_solo3,
  p_volume3,
  p_pan3,
  p_in4,
  p_mute4,
  p_solo4,
  p_volume4,
  p_pan4,
  p_outL,
  p_outR,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 10, 1, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 2, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* ams_lv__stereomixer__ch_ttl_hpp */
