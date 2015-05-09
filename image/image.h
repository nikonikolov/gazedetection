/*
 * image.hpp
 *
 *  Created on: 5 May 2015
 *      Author: niko
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "../pixel/pixel.h"

class Image{

private:
	Pixel** ptr;
	int iheight;
	int iwidth;

public:
	Image (int height_in, int width_in);
	~Image();
	int height() const;
	int width() const;
	Pixel* operator[](int index) const;

};

#endif


