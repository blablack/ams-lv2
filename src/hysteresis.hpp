#ifndef HYSTERESIS_H
#define HYSTERESIS_H

using namespace lvtk;

class Hysteresis: public Plugin<Hysteresis>
{
	public:
		Hysteresis(double rate);
		void run(uint32_t nframes);

	private:
		float currentsegment;
};

#endif
