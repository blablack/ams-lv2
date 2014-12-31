#ifndef MOOGLPF_H
#define MOOGLPF_H

using namespace lvtk;

class MoogLPF: public Plugin<MoogLPF>
{
	public:
		MoogLPF(double rate);
		void run(uint32_t nframes);

	private:
		float _c1, _c2, _c3, _c4, _c5, _w, _r;
		double m_rate;

		float exp2ap (float x);
};

#endif
