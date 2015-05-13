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
#include <vector>
//#include "../process_loci/process_loci.cpp"

typedef unsigned char byte;
#define FIL_DIM 5		//Note: must be an odd number
#define FIL_EDGE 3
#define WHITE 255
#define BLACK 0

#define EDGETRESH 50
#define TRESHOLD 110
//#define TRESHOLD 0.15

#define REGION 5
#define EROSION 3
#define DILATION 3

#define NEWMIN 50
#define NEWMAX 130


#define RADIUS 201
#define COLOR 220
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

const int FILE_TYPE_JPEG = 2;
const int FILE_TYPE_ERR = -1;

int get_file_type(const char * filename);
void convolute(int filter[FIL_DIM][FIL_DIM], const Image& input, const int& y, const int& x, Image& output);
void apply_filter(int filter[FIL_DIM][FIL_DIM], const Image& input, Image& output);
void convolute(double filter[FIL_DIM][FIL_DIM], const Image& input, const int& y, const int& x, Image& output);
void apply_filter(double filter[FIL_DIM][FIL_DIM], const Image& input, Image& output);
void array_to_image(unsigned char** in, Image& out);
void image_to_array(Image& in, unsigned char** out);
void find_color(const Pixel& color, const int& treshold, const Image& input, Image& output);
void grayscale(const Image& input, Image& output);
byte rgb_to_v_int(const Pixel& in);
double rgb_to_v(const Pixel& in);
void YCbCr(double& Y, double& Cb, double& Cr, const Pixel& input);
void convert(const Image& input, Image& output);
byte rgb_to_l(const Pixel& in);
//void treshold(const int& tresh, const Image& input, Image& output);
void convolute_edge(int filx[FIL_EDGE][FIL_EDGE], int fily[FIL_EDGE][FIL_EDGE], const Image& input, const int& y, const int& x, Image& output);
void edge(int filx[FIL_EDGE][FIL_EDGE], int fily[FIL_EDGE][FIL_EDGE], const Image& input, Image& output);


void find_centre(vector<vector<int>>& centre, Image& output);
void circle_centre(const int& b, const int& a, const int& height, const int& width, vector<vector<int>>& centre);
void edge(int filx[FIL_EDGE][FIL_EDGE], int fily[FIL_EDGE][FIL_EDGE], const Image& input, Image& output, vector<vector<int>>& centre);
void convolute_edge(int filx[FIL_EDGE][FIL_EDGE], int fily[FIL_EDGE][FIL_EDGE], const Image& input, const int& y, const int& x, Image& output,
					vector<vector<int>>& centre);

void morph_edge(const Image& input, Image& output, vector<vector<int>>& centre);

void normalize(const Image& input, Image& output);

void clear(const Image& input, Image& output);

void skin(const Image& input, vector<vector<int>>& bin);
void dilation(const vector<vector<int>>& input, vector<vector<int>>& output);
void erosion(const vector<vector<int>>& input, vector<vector<int>>& output);
void skin_back(Image& input, const vector<vector<int>>& bin);

#endif


