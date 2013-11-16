#ifndef FORGE_H
#define FORGE_H

#include <string>

#include <lvtk-1/lvtk/ext/atom.hpp>

using namespace lvtk;

class Forge:public AtomForge
{
public:
    Forge(LV2_URID_Map* map);

    ForgeRef forge_atom(uint32_t size, uint32_t type);
    void forge_pad(uint32_t written);
    void write_vector_float(uint32_t type, uint32_t nframes, float* data);
};

#endif

