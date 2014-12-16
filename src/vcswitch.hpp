#ifndef VCSWITCH_H
#define VCSWITCH_H

using namespace lvtk;

class VCSwitch: public Plugin<VCSwitch>
{
	private:
		float switchlevel;
	public:
		VCSwitch(double rate);
		void run(uint32_t nframes);
};

#endif
