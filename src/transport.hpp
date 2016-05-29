#ifndef TRANSPORT_H
#define TRANSPORT_H

using namespace lvtk;

class Transport: public Plugin<Transport, URID<true>>
{
	struct TransportURIs {
			LV2_URID atom_Blank;
			LV2_URID atom_Float;
			LV2_URID atom_Object;
			LV2_URID atom_Path;
			LV2_URID atom_Resource;
			LV2_URID atom_Sequence;
			LV2_URID time_Position;
			LV2_URID time_barBeat;
			LV2_URID time_beatsPerMinute;
			LV2_URID time_speed;
	} urids;

	public:
		Transport(double rate);
		void run(uint32_t nframes);
};

#endif
