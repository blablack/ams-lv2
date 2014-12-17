#include <lvtk-1/lvtk/plugin.hpp>

#include "seq.hpp"

#if STEP_COUNT == 8
#include "seq_8_ttl.hpp"
#undef SEQLEN
#define SEQLEN	8
#elif STEP_COUNT == 12
#include "seq_12_ttl.hpp"
#undef SEQLEN
#define SEQLEN	12
#elif STEP_COUNT == 16
#include "seq_16_ttl.hpp"
#undef SEQLEN
#define SEQLEN	16
#elif STEP_COUNT == 24
#include "seq_24_ttl.hpp"
#undef SEQLEN
#define SEQLEN	24
#elif STEP_COUNT == 32
#include "seq_32_ttl.hpp"
#undef SEQLEN
#define SEQLEN	32
#endif


Seq::Seq(double rate): Plugin<Seq>(p_n_ports)
{
	m_rate = rate;
	triggerCount = 0;
	trigger = false;
	triggerOut = false;
	seq_gate = 0;
	seq_freq = 0;
	seq_velocity = 0;
	tickFramesRemain = 0;
	tick = 0;
	seq_pos = 0;
	tickFrames = 0;
}

void Seq::run(uint32_t nframes)
{
	if (triggerCount)
	{
		triggerCount--;
	}
	else
	{
		for (unsigned int l2 = 0; l2 < nframes; l2++)
		{
			if (!trigger && (p(p_in_trigger)[l2] > 0.5))
			{
				trigger = true;
				triggerCount = 32;
			}
		}
	}

	tickFrames -= nframes;
	if (tickFrames <= 0)
		nextStep();

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_out_trigger)[l2] = (triggerOut) ? 1.0 : 0;
		p(p_gate)[l2] = seq_gate;
		p(p_freq)[l2] = seq_freq;
		p(p_velocity)[l2] = seq_velocity;
	}
}

void Seq::nextStep()
{
	int len;
	int minuteFrames = m_rate * 60 + tickFramesRemain;

	int bpm = (int)(*p(p_bpm));
	tickFrames += minuteFrames / (bpm << 4);
	tickFramesRemain = minuteFrames % (bpm << 4);

	if (trigger) {
		tick = 0;
		seq_pos = 0;
		trigger = false;
	}
	if (seq_pos == 0)
		triggerOut = true;
	else
		triggerOut = false;

	len = 4 - (int)(*p(p_gateTime));

#if STEP_COUNT == 8
	float pitch[STEP_COUNT] = {*p(p_pitch1), *p(p_pitch2), *p(p_pitch3), *p(p_pitch4), *p(p_pitch5), *p(p_pitch6), *p(p_pitch7), *p(p_pitch8)};
	float gate[STEP_COUNT] = {*p(p_gate1), *p(p_gate2), *p(p_gate3), *p(p_gate4), *p(p_gate5), *p(p_gate6), *p(p_gate7), *p(p_gate8)};
	float velocity[STEP_COUNT] = {*p(p_velocity1), *p(p_velocity2), *p(p_velocity3), *p(p_velocity4), *p(p_velocity5), *p(p_velocity6), *p(p_velocity7), *p(p_velocity8)};
#elif STEP_COUNT == 12
	float pitch[STEP_COUNT] = {*p(p_pitch1), *p(p_pitch2), *p(p_pitch3), *p(p_pitch4), *p(p_pitch5), *p(p_pitch6), *p(p_pitch7), *p(p_pitch8), *p(p_pitch9), *p(p_pitch10), *p(p_pitch11), *p(p_pitch12)};
	float gate[STEP_COUNT] = {*p(p_gate1), *p(p_gate2), *p(p_gate3), *p(p_gate4), *p(p_gate5), *p(p_gate6), *p(p_gate7), *p(p_gate8), *p(p_gate9), *p(p_gate10), *p(p_gate11), *p(p_gate12)};
	float velocity[STEP_COUNT] = {*p(p_velocity1), *p(p_velocity2), *p(p_velocity3), *p(p_velocity4), *p(p_velocity5), *p(p_velocity6), *p(p_velocity7), *p(p_velocity8), *p(p_velocity9), *p(p_velocity10), *p(p_velocity11), *p(p_velocity12)};
#elif STEP_COUNT == 16
	float pitch[STEP_COUNT] = {*p(p_pitch1), *p(p_pitch2), *p(p_pitch3), *p(p_pitch4), *p(p_pitch5), *p(p_pitch6), *p(p_pitch7), *p(p_pitch8), *p(p_pitch9), *p(p_pitch10), *p(p_pitch11), *p(p_pitch12), *p(p_pitch13), *p(p_pitch14), *p(p_pitch15), *p(p_pitch16)};
	float gate[STEP_COUNT] = {*p(p_gate1), *p(p_gate2), *p(p_gate3), *p(p_gate4), *p(p_gate5), *p(p_gate6), *p(p_gate7), *p(p_gate8), *p(p_gate9), *p(p_gate10), *p(p_gate11), *p(p_gate12), *p(p_gate13), *p(p_gate14), *p(p_gate15), *p(p_gate16)};
	float velocity[STEP_COUNT] = {*p(p_velocity1), *p(p_velocity2), *p(p_velocity3), *p(p_velocity4), *p(p_velocity5), *p(p_velocity6), *p(p_velocity7), *p(p_velocity8), *p(p_velocity9), *p(p_velocity10), *p(p_velocity11), *p(p_velocity12), *p(p_velocity13), *p(p_velocity14), *p(p_velocity15), *p(p_velocity16)};
#elif STEP_COUNT == 24
	float pitch[STEP_COUNT] = {*p(p_pitch1), *p(p_pitch2), *p(p_pitch3), *p(p_pitch4), *p(p_pitch5), *p(p_pitch6), *p(p_pitch7), *p(p_pitch8), *p(p_pitch9), *p(p_pitch10), *p(p_pitch11), *p(p_pitch12), *p(p_pitch13), *p(p_pitch14), *p(p_pitch15), *p(p_pitch16), *p(p_pitch17), *p(p_pitch18), *p(p_pitch19), *p(p_pitch20), *p(p_pitch21), *p(p_pitch22), *p(p_pitch23), *p(p_pitch24)};
	float gate[STEP_COUNT] = {*p(p_gate1), *p(p_gate2), *p(p_gate3), *p(p_gate4), *p(p_gate5), *p(p_gate6), *p(p_gate7), *p(p_gate8), *p(p_gate9), *p(p_gate10), *p(p_gate11), *p(p_gate12), *p(p_gate13), *p(p_gate14), *p(p_gate15), *p(p_gate16), *p(p_gate17), *p(p_gate18), *p(p_gate19), *p(p_gate20), *p(p_gate21), *p(p_gate22), *p(p_gate23), *p(p_gate24)};
	float velocity[STEP_COUNT] = {*p(p_velocity1), *p(p_velocity2), *p(p_velocity3), *p(p_velocity4), *p(p_velocity5), *p(p_velocity6), *p(p_velocity7), *p(p_velocity8), *p(p_velocity9), *p(p_velocity10), *p(p_velocity11), *p(p_velocity12), *p(p_velocity13), *p(p_velocity14), *p(p_velocity15), *p(p_velocity16), *p(p_velocity19), *p(p_velocity20), *p(p_velocity21), *p(p_velocity22), *p(p_velocity23), *p(p_velocity24)};
#elif STEP_COUNT == 32
	float pitch[STEP_COUNT] = {*p(p_pitch1), *p(p_pitch2), *p(p_pitch3), *p(p_pitch4), *p(p_pitch5), *p(p_pitch6), *p(p_pitch7), *p(p_pitch8), *p(p_pitch9), *p(p_pitch10), *p(p_pitch11), *p(p_pitch12), *p(p_pitch13), *p(p_pitch14), *p(p_pitch15), *p(p_pitch16), *p(p_pitch17), *p(p_pitch18), *p(p_pitch19), *p(p_pitch20), *p(p_pitch21), *p(p_pitch22), *p(p_pitch23), *p(p_pitch24), *p(p_pitch25), *p(p_pitch26), *p(p_pitch27), *p(p_pitch28), *p(p_pitch29), *p(p_pitch30), *p(p_pitch31), *p(p_pitch32)};
	float gate[STEP_COUNT] = {*p(p_gate1), *p(p_gate2), *p(p_gate3), *p(p_gate4), *p(p_gate5), *p(p_gate6), *p(p_gate7), *p(p_gate8), *p(p_gate9), *p(p_gate10), *p(p_gate11), *p(p_gate12), *p(p_gate13), *p(p_gate14), *p(p_gate15), *p(p_gate16), *p(p_gate17), *p(p_gate18), *p(p_gate19), *p(p_gate20), *p(p_gate21), *p(p_gate22), *p(p_gate23), *p(p_gate24), *p(p_gate25), *p(p_gate26), *p(p_gate27), *p(p_gate28), *p(p_gate29), *p(p_gate30), *p(p_gate31), *p(p_gate32)};
	float velocity[STEP_COUNT] = {*p(p_velocity1), *p(p_velocity2), *p(p_velocity3), *p(p_velocity4), *p(p_velocity5), *p(p_velocity6), *p(p_velocity7), *p(p_velocity8), *p(p_velocity9), *p(p_velocity10), *p(p_velocity11), *p(p_velocity12), *p(p_velocity13), *p(p_velocity14), *p(p_velocity15), *p(p_velocity16), *p(p_velocity19), *p(p_velocity20), *p(p_velocity21), *p(p_velocity22), *p(p_velocity23), *p(p_velocity24), *p(p_velocity25), *p(p_velocity26), *p(p_velocity27), *p(p_velocity28), *p(p_velocity29), *p(p_velocity30), *p(p_velocity31), *p(p_velocity32)};
#endif

	if (tick == 0) {
		seq_freq = float(pitch[seq_pos] + *p(p_pitchOffset)) / 12.0;

		seq_gate = (float)gate[seq_pos];
		seq_velocity = float(velocity[seq_pos]) / 127.0;
		seq_pos++;
		if (seq_pos >= SEQLEN)
			seq_pos = 0;
	}
	if (tick == len)
		seq_gate = 0;

	tick++;
	if (tick >= 4)
		tick = 0;
}

#if STEP_COUNT == 8
static int _ = Seq::register_class("http://github.com/blablack/ams-lv2/seq_8");
#elif STEP_COUNT == 12
static int _ = Seq::register_class("http://github.com/blablack/ams-lv2/seq_12");
#elif STEP_COUNT == 16
static int _ = Seq::register_class("http://github.com/blablack/ams-lv2/seq_16");
#elif STEP_COUNT == 24
static int _ = Seq::register_class("http://github.com/blablack/ams-lv2/seq_24");
#elif STEP_COUNT == 32
static int _ = Seq::register_class("http://github.com/blablack/ams-lv2/seq_32");
#endif

