#ifndef ams_lv__seq____ttl_hpp
#define ams_lv__seq____ttl_hpp


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

/* <http://github.com/blablack/ams-lv2/seq_16> */

static const char p_uri[] = "http://github.com/blablack/ams-lv2/seq_16";

enum p_port_enum {
  p_in_trigger,
  p_gate,
  p_freq,
  p_velocity,
  p_out_trigger,
  p_pitchOffset,
  p_bpm,
  p_gateTime,
  p_pitch1,
  p_pitch2,
  p_pitch3,
  p_pitch4,
  p_pitch5,
  p_pitch6,
  p_pitch7,
  p_pitch8,
  p_pitch9,
  p_pitch10,
  p_pitch11,
  p_pitch12,
  p_pitch13,
  p_pitch14,
  p_pitch15,
  p_pitch16,
  p_gate1,
  p_gate2,
  p_gate3,
  p_gate4,
  p_gate5,
  p_gate6,
  p_gate7,
  p_gate8,
  p_gate9,
  p_gate10,
  p_gate11,
  p_gate12,
  p_gate13,
  p_gate14,
  p_gate15,
  p_gate16,
  p_velocity1,
  p_velocity2,
  p_velocity3,
  p_velocity4,
  p_velocity5,
  p_velocity6,
  p_velocity7,
  p_velocity8,
  p_velocity9,
  p_velocity10,
  p_velocity11,
  p_velocity12,
  p_velocity13,
  p_velocity14,
  p_velocity15,
  p_velocity16,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 63, 32, 0, 0, 0 }, 
  { 3, 300, 120, 0, 0, 0 }, 
  { 0, 3, 0, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 64, 31, 0, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
  { 0, 127, 63, 0, 0, 0 }, 
};


#endif /* ams_lv__seq____ttl_hpp */
