#ifndef ams_lv__transport_ttl_hpp
#define ams_lv__transport_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/transport> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/transport";

enum p_port_enum {
  p_time,
  p_play,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__transport_ttl_hpp */
