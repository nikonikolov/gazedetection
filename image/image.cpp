/*
 * image.cpp
 *
 *  Created on: 5 May 2015
 *      Author: niko
 */
#include "image.h"

	Image::Image (int height_in, int width_in){
		iheight=height_in;
		iwidth=width_in;
		ptr=new Pixel* [iheight];
		for(int i=0; i<iheight; i++){
			ptr[i]= new Pixel [iwidth];
		}

	}

	Image::~Image(){
		for(int i=0; i<iheight; i++){
			delete[] ptr[i];
		}
		delete[] ptr;
	}

	int Image::height() const{
		return iheight;
	}

	int Image::width() const{
		return iwidth;
	}

	Pixel* Image::operator[](int index) const{
		return ptr[index];
	}
