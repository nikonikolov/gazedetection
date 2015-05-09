/*
 * pixel.cpp
 *
 *  Created on: 5 May 2015
 *      Author: niko
 */
#include "pixel.h"

	Pixel::Pixel(unsigned char red_in/*=0*/, unsigned char green_in/*=0*/, unsigned char blue_in/*=0*/){
		pred=red_in;
		pgreen=green_in;
		pblue=blue_in;
	}

	/*Pixel::Pixel(unsigned char grayscale_in){
		pred=grayscale_in;
		pgreen=grayscale_in;
		pblue=grayscale_in;
	}*/

	unsigned char Pixel::red() const{
		return pred;
	}

	unsigned char Pixel::green() const{
		return pgreen;
	}

	unsigned char Pixel::blue() const{
		return pblue;
	}

	void Pixel::set_red(const unsigned char& red_in){
		pred=red_in;
	}
	void Pixel::set_green(const unsigned char& green_in){
		pgreen=green_in;
	}
	void Pixel::set_blue(const unsigned char& blue_in){
		pblue=blue_in;
	}

	void Pixel::set_rgb(const unsigned char& red_in, const unsigned char& green_in, const unsigned char& blue_in){
		pred=red_in;
		pgreen=green_in;
		pblue=blue_in;
	}

	void Pixel::set_intensity(const unsigned char& intensity_in){
		pred=intensity_in;
		pgreen=intensity_in;
		pblue=intensity_in;
	}

	void Pixel::set_to_pix(const Pixel& pix_in){
		pred=pix_in.pred;
		pgreen=pix_in.pgreen;
		pblue=pix_in.pblue;
	}

	ostream& operator<<(ostream& out, const Pixel& pix_in){
		out<<(int)pix_in.pred<<" "<<(int)pix_in.pgreen<<" "<<(int)pix_in.pblue<<endl;
		return out;
	}
