🚨 This project is archived and no longer maintained. 🚨

Thank you for your past support. Feel free to explore the existing codebase and documentation. For any questions, consider checking the existing issues, but note that responses may be delayed.

If you find this project useful and wish to continue its development, please fork it with proper attribution and adherence to the license.

ams-lv2
=======

This set of LV2 plugins is a port of the internal modules found in Alsa Modular Synth [http://alsamodular.sourceforge.net/](http://alsamodular.sourceforge.net/).

These plugins are used to create modular synthesizers and contains:
- VCO
- VCF
- VCA
- LFO
- Slew Limiter
- Envelop
- Sample & Hold
- etc.

More information can be found here:
[http://objectivewave.wordpress.com/ams-lv2](http://objectivewave.wordpress.com/ams-lv2)


INSTALL
-------

	$  ./waf configure
	$  ./waf 
	$  ./waf install


RUNNING
-------

After the INSTALL step any LV2 host should automatically find the plugins and add them to the list of loadable ones.

Ingen is the recommended host.
More information about Ingen here: [http://drobilla.net/software/ingen/](http://drobilla.net/software/ingen/)


BUG REPORTING
-------------
Please use the issue tracker on github to report bugs:
[http://github.com/blablack/ams-lv2/issues](http://github.com/blablack/ams-lv2/issues)



