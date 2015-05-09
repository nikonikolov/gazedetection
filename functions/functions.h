/*
 * functions.h
 *
 *  Created on: 8 May 2015
 *      Author: niko
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <math.h>
#include "../pixel/pixel.h"
#include "../image/image.h"
//#include "../process_loci/process_loci.cpp"

typedef unsigned char byte;
#define FIL_DIM 3		//Note: must be an odd number
#define WHITE 255
#define BLACK 0
#define TRESHOLD 20
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

const int FILE_TYPE_JPEG = 2;
const int FILE_TYPE_ERR = -1;

int get_file_type(const char * filename);
void convolute(int filter[FIL_DIM][FIL_DIM], const Image& input, const int y, const int x, Image& output);
void apply_filter(int filter[FIL_DIM][FIL_DIM], const Image& input, Image& output);
void convolute(double filter[FIL_DIM][FIL_DIM], const Image& input, const int y, const int x, Image& output);
void apply_filter(double filter[FIL_DIM][FIL_DIM], const Image& input, Image& output);
void array_to_image(unsigned char** in, Image& out);
void image_to_array(Image& in, unsigned char** out);
void find_color(const Pixel& color, const int& treshold, const Image& input, Image& output);

#endif


