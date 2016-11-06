#include <lvtk-1/lvtk/plugin.hpp>

#include "vcpanning.hpp"
#include "vcpanning_ttl.hpp"

VCPanning::VCPanning(double rate): Plugin<VCPanning>(p_n_ports)
{
}

void VCPanning::run(uint32_t nframes)
{
	int l2, k, len;
	double dpan[2], x, y, x_2, widthConst;

	widthConst = 2.0 / 88.0;

	len = nframes;
	l2 = -1;

	int p_panMode = (int)(*p(p_panningMode));

	do
	{
		k = (len > 24) ? 16 : len;
		l2 += k;
		len -= k;
		switch (p_panMode)
		{
			case 0:
				x = *p(p_panOffset) + *p(p_panGain) * p(p_panCV)[l2];
				x_2 = 0.5 * x;
				if (x < -1)
					x = -1;
				if (x > 1)
					x = 1;
				y = 0.2125 * (1.0 - x * x);
				pan[1] = (0.5 + x_2) + y;
				pan[0] = (0.5 - x_2) + y;
				break;
			case 1:
				x = panPos;
				x_2 = 0.5 * x;
				y = 0.2125 * (1.0 - x * x);
				pan[1] = (0.5 + x_2) + y;
				pan[0] = (0.5 - x_2) + y;
				break;
			case 2:
				x = 0.5 * panPos;
				x_2 = 0.5 * x;
				y = 0.2125 * (1.0 - x * x);
				pan[1] = (0.5 + x_2) + y;
				pan[0] = (0.5 - x_2) + y;
				break;
			case 3:
				x = 0.25 * panPos;
				x_2 = 0.5 * x;
				y = 0.2125 * (1.0 - x * x);
				pan[1] = (0.5 + x_2) + y;
				pan[0] = (0.5 - x_2) + y;
				break;
			case 4:
				pan[1] = 1;
				pan[0] = 1;
				break;
		}
		dpan[0] = (pan[0] - oldpan[0]) / (double) k;
		dpan[1] = (pan[1] - oldpan[1]) / (double) k;
		while (k--)
		{
			oldpan[0] += dpan[0];
			oldpan[1] += dpan[1];
			p(p_out1)[l2 - k] = oldpan[0] * p(p_in)[l2 - k];
			p(p_out2)[l2 - k] = oldpan[1] * p(p_in)[l2 - k];
		}
	} while (len);

}

static int _ = VCPanning::register_class("http://github.com/blablack/ams-lv2/vcpanning");

