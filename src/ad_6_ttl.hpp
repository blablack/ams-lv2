#ifndef ams_lv__ad___ttl_hpp
#define ams_lv__ad___ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/ad_6> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/ad_6";

enum p_port_enum {
  p_cvIn,
  p_detuneAmplitude,
  p_detuneModulation,
  p_detuneRate,
  p_driftAmplitude,
  p_driftModulation,
  p_driftRate,
  p_cvOut1,
  p_cvOut2,
  p_cvOut3,
  p_cvOut4,
  p_cvOut5,
  p_cvOut6,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 0.084, 0.005, 0, 0, 0 }, 
  { 0.01, 1, 0.01, 0, 0, 0 }, 
  { 0.01, 10, 1, 0, 0, 0 }, 
  { 0, 0.084, 0.005, 0, 0, 0 }, 
  { 0.01, 1, 0.01, 0, 0, 0 }, 
  { 0.01, 10, 3, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__ad___ttl_hpp */
