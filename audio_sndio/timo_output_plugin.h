///*
 //* Copyright 2008-2013 Various Authors
 //* Copyright 2004 Timo Hirvonen
 //*
 //* This program is free software; you can redistribute it and/or
 //* modify it under the terms of the GNU General Public License as
 //* published by the Free Software Foundation; either version 2 of the
 //* License, or (at your option) any later version.
 //*
 //* This program is distributed in the hope that it will be useful, but
 //* WITHOUT ANY WARRANTY; without even the implied warranty of
 //* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 //* General Public License for more details.
 //*
 //* You should have received a copy of the GNU General Public License
 //* along with this program; if not, see <http://www.gnu.org/licenses/>.
 //*/

//#ifndef CMUS_OP_H
//#define CMUS_OP_H
#pragma once
//#include "timo_sample_format.h"
//#include "johannes_channel_map.h"

//#ifndef __GNUC__
//#include <fcntl.h>
//#endif

//#define OP_ABI_VERSION 3


//struct output_plugin_ops {
	//int (*init)(void);
	//int (*exit)(void);
	//int (*open)(sample_format_t sf, const channel_position_t *channel_map);
	//int (*close)(void);
	//int (*drop)(void);
	//int (*write)(const_char_pointer buffer, int count);
	//int (*buffer_space)(void);

	///* these can be NULL */
	//int (*pause)(void);
	//int (*unpause)(void);

//};

//#define OPT(prefix, name) { #name, prefix ## _set_ ## name, \
	//prefix ## _get_ ## name }

//struct output_plugin_opt {
	//const_char_pointer name;
	//int (*set)(const_char_pointer val);
	//int (*get)(char **val);
//};

///* symbols exported by plugin */
//extern const struct output_plugin_ops op_pcm_ops;
//extern const struct output_plugin_opt op_pcm_options[];
//extern const int op_priority;
//extern const unsigned op_abi_version;

//#endif
