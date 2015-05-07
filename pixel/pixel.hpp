/*
 * pixel.hpp
 *
 *  Created on: 5 May 2015
 *      Author: niko
 */
#ifndef PIXEL_H
#define PIXEL_H
#include<ostream>
#include<iostream>
using namespace std;

class Pixel{

private:
	unsigned char pred;
	unsigned char pgreen;
	unsigned char pblue;

public:

	Pixel(unsigned char red_in=0, unsigned char green_in=0, unsigned char blue_in=0);
	//Pixel(unsigned char grayscale_in);
	unsigned char red() const;
	unsigned char green() const;
	unsigned char blue() const;
	void set_red(const unsigned char& red_in);
	void set_green(const unsigned char& green_in);
	void set_blue(const unsigned char& blue_in);
	void set_rgb(const unsigned char& red_in, const unsigned char& green_in, const unsigned char& blue_in);
	void set_intensity(const unsigned char& intensity_in);
	void set_to_pix(const Pixel& pix_in);
	friend ostream& operator<<(ostream& out, const Pixel& pix_in);

};

#endif




