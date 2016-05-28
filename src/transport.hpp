#ifndef TRANSPORT_H
#define TRANSPORT_H

using namespace lvtk;

class Transport: public Plugin<Transport>
{
	public:
		Transport(double rate);
		void run(uint32_t nframes);
};

#endif
