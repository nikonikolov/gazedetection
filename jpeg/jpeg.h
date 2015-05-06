/*
 * jpeg.h
 *
 *  Created on: 3 May 2015
 *      Author: niko
 */
#ifndef JPEG_ENCDEC_LIB
#define JPEG_ENCDEC_LIB

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <jpeglib.h>
#include <magic.h>
#include "../file/file.h"	// for function file_check_type in jpeg.cpp

bool jpeg_check_file(const char * filename);
void jpeg_decode(const char * filename, int & height, int & width, int & components, unsigned char ** & matrix);
void jpeg_encode(const char * filename, int height, int width, int components, unsigned char ** matrix);
void jpeg_encode_grayscale(const char * filename, int height, int width, unsigned char ** matrix);

#endif



