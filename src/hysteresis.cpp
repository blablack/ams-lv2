#include <lvtk-1/lvtk/plugin.hpp>

#include "hysteresis.hpp"
#include "hysteresis_ttl.hpp"

Hysteresis::Hysteresis(double rate): Plugin<Hysteresis>(p_n_ports)
{
}

void Hysteresis::run(uint32_t nframes)
{
}

static int _ = Hysteresis::register_class("http://github.com/blablack/ams-lv2/hysteresis");

