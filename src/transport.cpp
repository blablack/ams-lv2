#include <lvtk-2/lvtk/plugin.hpp>

#include "transport.hpp"
#include "transport_ttl.hpp"

Transport::Transport(double rate): Plugin<Transport>(p_n_ports)
{
}

void Transport::run(uint32_t nframes)
{
}

static int _ = Transport::register_class("http://github.com/blablack/ams-lv2/transport");

