#include <lvtk-1/lvtk/plugin.hpp>

#include "vcenv.hpp"
#include "vcenv_ttl.hpp"

VCEnv::VCEnv(double rate): Plugin<VCEnv> (p_n_ports)
{
}

void VCEnv::run(uint32_t nframes)
{

}

static int _ = VCEnv::register_class("http://github.com/blablack/ams-lv2/vcenv");

