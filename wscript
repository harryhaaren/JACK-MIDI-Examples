#!/usr/bin/python

def set_options(opt):
	print '\nSetting build options & flags...'
	# We tell Waf we need a C++ compiler
	opt.tool_options('compiler_cxx')

def init():
	print 'Initializing WAF build system...'
	

def configure(conf):
	print 'Configuring the build enviroment...'
	
	conf.check_tool('compiler_cxx')
	conf.check_cfg	(package='jack',at_least_version='1.0.0',args='--cflags --libs',uselib_store='JACK')

def build(bld):
	print 'Building the sources to objects...'
	
	# Builds the jack.cpp file to an object file
	bld.new_task_gen(
		features	= 'cxx cstaticlib',
		source		= 'jack.cpp',
		includes	= '/usr/include',
		uselib		= 'JACK',
		target		= 'jackClass',
		export_dirs	= '.'	)
	
	bld.new_task_gen(
		features	= 'cxx cprogram',
		source		= 'main.cpp',
		includes	= '/usr/include',
		uselib		= 'GTKMM',
		uselib_local= 'jackClass', # here we link the jack.o file to the executable
		target		= 'test.out'	)


