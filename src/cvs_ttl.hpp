#ifndef ams_lv__cvs_ttl_hpp
#define ams_lv__cvs_ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/cvs> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/cvs";

enum p_port_enum {
  p_cv1,
  p_cvFine1,
  p_cvOut1,
  p_cv2,
  p_cvFine2,
  p_cvOut2,
  p_cv3,
  p_cvFine3,
  p_cvOut3,
  p_cv4,
  p_cvFine4,
  p_cvOut4,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 5, 0, 0, 0, 0 }, 
  { -0.5, 0.5, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 5, 0, 0, 0, 0 }, 
  { -0.5, 0.5, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 5, 0, 0, 0, 0 }, 
  { -0.5, 0.5, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { 0, 5, 0, 0, 0, 0 }, 
  { -0.5, 0.5, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* ams_lv__cvs_ttl_hpp */
