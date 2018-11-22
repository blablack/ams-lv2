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

    #autowaf.check_pkg(conf, 'gtkmm-2.4',  uselib_store='GTKMM',atleast_version='2.24.0', mandatory=True)
    #autowaf.check_pkg(conf, 'gtk+-2.0', uselib_store='GTK2', atleast_version='2.24.0', mandatory=True)
    autowaf.check_pkg(conf, 'cairo', uselib_store='CAIRO', atleast_version='1.10.0', mandatory=True)
    autowaf.check_pkg(conf, 'lv2', uselib_store='LV2', atleast_version='1.10.0', mandatory=True)
    autowaf.check_pkg(conf, 'lvtk-plugin-1', uselib_store='LVTK_PLUGIN', atleast_version='1.2.0')
    #autowaf.check_pkg(conf, 'lvtk-ui-1', uselib_store='LVTK_UI', atleast_version='1.2.0')
    #autowaf.check_pkg(conf, 'lvtk-gtkui-1', uselib_store='LVTK_GTKGUI', atleast_version='1.2.0')
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
    
    #install modgui
    bld.install_files('${LV2DIR}/' + bundle, os.path.join(bundle, 'modgui'))

def build_plugin_gui(bld, bundle, name, source, cxxflags=[], cppflags=[], libs=[], add_source=[]):
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


def build(bld):
    def do_copy(task):
        src = task.inputs[0].abspath()
        tgt = task.outputs[0].abspath()
        return shutil.copy(src, tgt)

    for i in bld.path.ant_glob('mod-ams.lv2/*.ttl'):
        bld(features     = 'subst',
            is_copy      = True,
            source       = i,
            target       = 'mod-ams.lv2/%s' % i.name, 'mod-ams.lv2/modgui/*',
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

########################################################################
#
#    plugins = '''
#    2
#    4
#    6
#    '''.split()
#
#    for i in plugins:
#       build_plugin(bld, 'ams.lv2', "ad_%s" % i, ['src/ad.cpp'],
#                    ['-DPLUGIN_CLASS=ad_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="ad_%s"' % i,
#                     '-DPLUGIN_HEADER="src/ad.hpp"'],
#                    ['-DOUT_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', "ad_%s_gui" % i, ['src/ad_gui.cpp'],
#                        ['-DPLUGIN_CLASS=ad_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="ad_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/ad_gui.hpp"'],
#                        ['-DOUT_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp'])
#
########################################################################

#    plugins = '''
#    4
#    6
#    8
#    '''.split()
#
#    for i in plugins:
#       build_plugin(bld, 'ams.lv2', 'dynamicwaves_%s' % i, ['src/dynamicwaves.cpp'],
#                    ['-DPLUGIN_CLASS=dynamicwaves_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="dynamicwaves_%s"' % i,
#                     '-DPLUGIN_HEADER="src/dynamicwaves.hpp"'],
#                    ['-DOSC_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', 'dynamicwaves_%s_gui' % i, ['src/dynamicwaves_gui.cpp'],
#                        ['-DPLUGIN_CLASS=dynamicwaves_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="dynamicwaves_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/dynamicwaves_gui.hpp"'],
#                        ['-DOSC_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp', 'src/dynamicwaves_scope.cpp'])
#
#       build_plugin(bld, 'ams.lv2', 'vcorgan_%s' % i, ['src/vcorgan.cpp'],
#                    ['-DPLUGIN_CLASS=vcorgan_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="vcorgan_%s"' % i,
#                     '-DPLUGIN_HEADER="src/vcorgan.hpp"'],
#                    ['-DOSC_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', 'vcorgan_%s_gui' % i, ['src/vcorgan_gui.cpp'],
#                        ['-DPLUGIN_CLASS=vcorgan_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="vcorgan_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/vcorgan_gui.hpp"'],
#                        ['-DOSC_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp'])
#
#       build_plugin(bld, 'ams.lv2', 'dynamicwaves2_%s' % i, ['src/dynamicwaves2.cpp'],
#                    ['-DPLUGIN_CLASS=dynamicwaves2_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="dynamicwaves2_%s"' % i,
#                     '-DPLUGIN_HEADER="src/dynamicwaves2.hpp"'],
#                    ['-DOSC_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', 'dynamicwaves2_%s_gui' % i, ['src/dynamicwaves2_gui.cpp'],
#                        ['-DPLUGIN_CLASS=dynamicwaves2_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="dynamicwaves2_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/dynamicwaves2_gui.hpp"'],
#                        ['-DOSC_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp', 'src/dynamicwaves_scope.cpp'])
#
#       build_plugin(bld, 'ams.lv2', 'vcorgan2_%s' % i, ['src/vcorgan2.cpp'],
#                    ['-DPLUGIN_CLASS=vcorgan2_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="vcorgan2_%s"' % i,
#                     '-DPLUGIN_HEADER="src/vcorgan2.hpp"'],
#                    ['-DOSC_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', 'vcorgan2_%s_gui' % i, ['src/vcorgan2_gui.cpp'],
#                        ['-DPLUGIN_CLASS=vcorgan2_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="vcorgan2_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/vcorgan2_gui.hpp"'],
#                        ['-DOSC_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp'])
#
#########################################################################
#
#    plugins = '''
#    8
#    12
#    16
#    24
#    32
#    '''.split()
#
#    for i in plugins:
#       build_plugin(bld, 'ams.lv2', 'seq_%s' % i, ['src/seq.cpp'],
#                    ['-DPLUGIN_CLASS=seq_%s' % i,
#                     '-std=c++11',
#                     '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                     '-DPLUGIN_URI_SUFFIX="seq_%s"' % i,
#                     '-DPLUGIN_HEADER="src/seq.hpp"'],
#                    ['-DSTEP_COUNT=%s' % i],
#                    ['LV2', 'LVTK_PLUGIN'],
#                    ['src/synthdata.cpp'])
#
#       build_plugin_gui(bld, 'ams.lv2', 'seq_%s_gui' % i, ['src/seq_gui.cpp'],
#                        ['-DPLUGIN_CLASS=seq_%s_gui' % i,
#                         '-std=c++11',
#                         '-DURI_PREFIX=\"http://github.com/blablack/ams-lv2/\"',
#                         '-DPLUGIN_URI_SUFFIX="seq_%s_gui"' % i,
#                         '-DPLUGIN_HEADER="src/seq_gui.hpp"'],
#                        ['-DSTEP_COUNT=%s' % i],
#                        ['LV2', 'LVTK_PLUGIN', 'LVTK_GTKGUI', 'GTKMM', 'GTK2', 'CAIRO'],
#                        ['src/dial.cpp', 'src/labeleddial.cpp', 'src/my_box.cpp'])
#
