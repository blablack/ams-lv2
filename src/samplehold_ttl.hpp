#ifndef ams_lv__samplehold_ttl_hpp
#define ams_lv__samplehold_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/samplehold> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/samplehold";

enum p_port_enum {
  p_triggerLevel,
  p_input,
  p_trigger,
  p_output,
  p_gate,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 10, 0.5, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__samplehold_ttl_hpp */
