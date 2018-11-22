#!/usr/bin/env python
import sys
import os
import subprocess
import shutil
from waflib import Logs
sys.path.insert(0, "tools/waf")
import autowaf

# Variables for 'waf dist'
APPNAME = 'mod-ams-lv2'
VERSION = '1.2.1'

# Mandatory variables
top = '.'
out = 'build'


def options(opt):
    autowaf.set_options(opt)
    opt.load('compiler_cxx')
    opt.load('lv2')


def configure(conf):
    autowaf.configure(conf)
    autowaf.display_header('mod-ams-lv2 Configuration')

    conf.load('compiler_cxx')
    conf.load('lv2')

    autowaf.check_pkg(conf, 'cairo', uselib_store='CAIRO', atleast_version='1.10.0', mandatory=True)
    autowaf.check_pkg(conf, 'lv2', uselib_store='LV2', atleast_version='1.10.0', mandatory=True)
    autowaf.check_pkg(conf, 'lvtk-plugin-1', uselib_store='LVTK_PLUGIN', atleast_version='1.2.0')
    autowaf.check_pkg(conf, 'fftw3', uselib_store='FFTW3', atleast_version='3.3.3', mandatory=True)

    check = 'Extended Initializer Lists'
    conf.check_cxx(msg         = check,
                   define_name = 'WAF_CXX_FEATURE_' + check.replace(' ', '_').upper(),
                   fragment    = '#include <vector>\n'+
                                 'struct foo {\n'+
                                 '  int i;\n'+
                                 '  int j;\n'+
                                 '  int k;\n'+
                                 '};\n'+
                                 'int main() {\n'+
                                 '  std::vector<foo> v(1);\n'+
                                 '  v[0] = {0, 0, 0};\n'+
                                 '  return 0;\n'+
                                 '}',
                   mandatory   = False)

    # Set env['pluginlib_PATTERN']
    pat = conf.env['cxxshlib_PATTERN']
    if pat[0:3] == 'lib':
        pat = pat[3:]
    conf.env['pluginlib_PATTERN'] = pat

    autowaf.display_msg(conf, "LV2 bundle directory", conf.env['LV2DIR'])
    print('')


def build_plugin(bld, bundle, name, source, cxxflags=[], cppflags=[], libs=[], add_source=[]):
    penv = bld.env.derive()
    penv['cxxshlib_PATTERN'] = bld.env['pluginlib_PATTERN']
    obj              = bld(features = 'cxx cxxshlib')
    obj.env          = penv
    obj.source       = source + add_source
    obj.includes     = ['.', './src']
    obj.name         = name
    obj.target       = os.path.join(bundle, name)
    if cxxflags != []:
        obj.cxxflags = cxxflags
    obj.cxxflags = obj.cxxflags + ['-msse', '-mfpmath=sse', '-ffast-math']
    if cppflags != []:
        obj.cppflags = cppflags
    if libs != []:
        obj.uselib = libs
    obj.install_path = '${LV2DIR}/' + bundle

    # Install data file
    data_file = '%s.ttl' % name
    bld.install_files('${LV2DIR}/' + bundle, os.path.join(bundle, data_file))

def build_ui(bld, bundle):
    
    bundlePath = os.path.join(bundle, 'modgui')

    for path, subdirs, files in os.walk(r'%s' % bundlePath):
        for filename in files:

            sPath = path.replace(bundlePath, '')
            totalPath = os.path.join(sPath, filename)
            joinedPath = ''.join(totalPath.split('/',1))
          
            gui_file = 'modgui/%s' % joinedPath
            bld.install_files('${LV2DIR}/' + bundle + '/modgui', os.path.join(bundle, gui_file))


def build(bld):
    def do_copy(task):
        src = task.inputs[0].abspath()
        tgt = task.outputs[0].abspath()
        return shutil.copy(src, tgt)

    for i in bld.path.ant_glob('mod-ams.lv2/*.ttl'):
        bld(features     = 'subst',
            is_copy      = True,
            source       = i,
            target       = 'mod-ams.lv2/%s' % i.name,
            install_path = '${LV2DIR}/mod-ams.lv2')


########################################################################

    plugins = '''
    env
    lfo2_freq
    vcalin
    '''.split()

    for i in plugins:
        build_plugin(bld, 'mod-ams.lv2', i, ['src/%s.cpp' % i],
                     ['-DPLUGIN_CLASS=%s' % i,
                      '-std=c++11',
                      '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
                      '-DPLUGIN_URI_SUFFIX="%s"' % i,
                      '-DPLUGIN_HEADER="src/%s.hpp"' % i],
                     [],
                     ['LV2', 'LVTK_PLUGIN'],
                     [])

########################################################################

    plugins = '''
    vcaexp
    vcf
    vco3
    '''.split()

    for i in plugins:
        build_plugin(bld, 'mod-ams.lv2', i, ['src/%s.cpp' % i],
                     ['-DPLUGIN_CLASS=%s' % i,
                      '-std=c++11',
                      '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
                      '-DPLUGIN_URI_SUFFIX="%s"' % i,
                      '-DPLUGIN_HEADER="src/%s.hpp"' % i],
                     [],
                     ['LV2', 'LVTK_PLUGIN'],
                     ['src/synthdata.cpp'])

########################################################################
    build_ui(bld, 'mod-ams.lv2')
########################################################################
