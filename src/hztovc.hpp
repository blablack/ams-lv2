#ifndef HZTOVC_H
#define HZTOVC_H

using namespace lvtk;

class HzToVc: public Plugin<HzToVc>
{
	public:
		HzToVc(double rate);
		void run(uint32_t nframes);

	private:
		float m_eighth, m_log2inv;
};

#endif
