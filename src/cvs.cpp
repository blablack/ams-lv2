#include <lvtk-1/lvtk/plugin.hpp>

#include "cvs.hpp"
#include "cvs_ttl.hpp"

Cvs::Cvs(double rate):	Plugin<Cvs>(p_n_ports)
{
}

void Cvs::run(uint32_t nframes)
{
	float cv1 = *p(p_cv1);
	float cvFine1 = *p(p_cvFine1);

	float cv2 = *p(p_cv2);
	float cvFine2 = *p(p_cvFine2);

	float cv3 = *p(p_cv3);
	float cvFine3 = *p(p_cvFine3);

	float cv4 = *p(p_cv4);
	float cvFine4 = *p(p_cvFine4);

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_cvOut1)[l2] = cv1 + cvFine1;
		p(p_cvOut2)[l2] = cv2 + cvFine2;
		p(p_cvOut3)[l2] = cv3 + cvFine3;
		p(p_cvOut4)[l2] = cv4 + cvFine4;
	}
}

static int _ = Cvs::register_class("http://github.com/blablack/ams-lv2/cvs");
