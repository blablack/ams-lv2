#ifndef HZTOVC_H
#define HZTOVC_H

using namespace lvtk;

class HzToVc: public Plugin<HzToVc>
{
	private:
		float m_eighth, m_log2inv;

	public:
		HzToVc(double rate);
		void run(uint32_t nframes);
};

#endif
