#ifndef SEQ_H
#define SEQ_H

using namespace lvtk;

class Seq: public Plugin<Seq>
{
	public:
		Seq(double rate);
		void run(uint32_t nframes);

	private:
		double m_rate;
		float seq_gate, seq_freq, seq_velocity;
		int seq_pos, tick, triggerCount, tickFrames, tickFramesRemain;
		bool trigger, triggerOut;

		void nextStep();
};

#endif
