/*
 * file.h
 *
 *  Created on: 3 May 2015
 *      Author: niko
 */
#ifndef FILE_H
#define FILE_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>		//tolower function in file.cpp
#include <magic.h>		//for recognizing file types

bool file_check_type(const char * filename, const char * ext);

#endif



