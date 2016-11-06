#include <lvtk-1/lvtk/plugin.hpp>

#include "transport.hpp"
#include "transport_ttl.hpp"

Transport::Transport(double rate): Plugin<Transport, URID<true>>(p_n_ports)
{
	urids.atom_Blank          = map (LV2_ATOM__Blank);
	urids.atom_Float          = map (LV2_ATOM__Float);
	urids.atom_Object         = map (LV2_ATOM__Object);
	urids.atom_Path           = map (LV2_ATOM__Path);
	urids.atom_Resource       = map (LV2_ATOM__Resource);
	urids.atom_Sequence       = map (LV2_ATOM__Sequence);
	urids.time_Position       = map (LV2_TIME__Position);
	urids.time_barBeat        = map (LV2_TIME__barBeat);
	urids.time_beatsPerMinute = map (LV2_TIME__beatsPerMinute);
	urids.time_speed          = map (LV2_TIME__speed);
}

void Transport::run(uint32_t nframes)
{
	bool p_trigger = false;

	const LV2_Atom_Sequence* transportseq = p<LV2_Atom_Sequence> (p_time);

	LV2_ATOM_SEQUENCE_FOREACH(transportseq, ev)
	{
		if (ev->body.type == urids.atom_Object)
		{
			const LV2_Atom_Object* obj = (const LV2_Atom_Object*)&ev->body;
			if (obj->body.otype == urids.time_Position)
			{
				p_trigger = true;
			}
		}
	}

	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		if(p_trigger)
			p(p_play)[l2] = 1;
		else
			p(p_play)[l2] = 0;
	}
}

static int _ = Transport::register_class("http://github.com/blablack/ams-lv2/transport");
