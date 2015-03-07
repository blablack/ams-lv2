#ifndef HAAS_H
#define HAAS_H

using namespace lvtk;

class Haas: public Plugin<Haas>
{
	public:
		Haas(double rate);
		~Haas();
		void run(uint32_t nframes);

	private:
		int m_buffer_size;
		double m_rate;

		float m_dry;
		float m_wet;

		int read_ofs;
		float *buf_l;
		float *buf_r;
};

#endif
