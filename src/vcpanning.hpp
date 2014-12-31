#ifndef VCPANNING_H
#define VCPANNING_H

using namespace lvtk;

class VCPanning: public Plugin<VCPanning>
{
	public:
		VCPanning(double rate);
		void run(uint32_t nframes);

	private:
		float panPos, pan[2], oldpan[2];
};

#endif
