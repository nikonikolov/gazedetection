/*
 * image.hpp
 *
 *  Created on: 5 May 2015
 *      Author: niko
 */
#include "../pixel/pixel.hpp"

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



