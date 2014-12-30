#ifndef ams_lv__analogmemory_ttl_hpp
#define ams_lv__analogmemory_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/analogmemory> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/analogmemory";

enum p_port_enum {
  p_input_cv,
  p_write_addr,
  p_write_ena,
  p_read_addr,
  p_write_addressing_mode,
  p_n,
  p_write_tresh,
  p_out_cv,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 5, 1, 0, 0, 0 }, 
  { 1, 20, 20, 0, 0, 0 }, 
  { -1, 1, -0.1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__analogmemory_ttl_hpp */
