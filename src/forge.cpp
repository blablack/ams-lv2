#include "forge.hpp"

using namespace lvtk;

Forge::Forge(LV2_URID_Map* map): AtomForge (map)
{
}

ForgeRef Forge::forge_atom(uint32_t size, uint32_t type)
{
    return lv2_atom_forge_atom(cobj(), size, type);
}

void Forge::forge_pad(uint32_t written)
{
    lv2_atom_forge_pad(cobj(), written);
}

void Forge::write_vector_float(uint32_t type, uint32_t nframes, float* data)
{
    lv2_atom_forge_vector(cobj(), sizeof(float), type, nframes, data);
}
