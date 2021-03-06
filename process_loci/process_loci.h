/*
*	Process file header by me
*
*/

#ifndef PROCESS_LOCI
#define PROCESS_LOCI

#include <cstdlib>
//#include <math.h>
#include "../pixel/pixel.h"
#include "../image/image.h"
//#include <../pixel/pixel.h>

class Process_loci{

private:
	void fill_rectangle(const Image& input, int centerX, int centerY, int dimension, Pixel color);
	void contrast(const Image& input, double mod_contrast);
	unsigned char multipAndBound(unsigned char orig, double mod_contrast);
	void brightness(const Image& input, int mod_brightness);
	unsigned char addAndBound(unsigned char orig, int mod_brightness);
	bool is_match(Pixel& pixel, Pixel color, Pixel treshold);
	int map_value(int value, int inMin, int inMax, int outMin, int outMax);

	void RGB_to_YUV(double& Y, double& U, double& V, const double& R, const double& G, const double& B);

public:
	void find_center(const Image& input, Pixel color, Pixel treshold,
					int boxX, int boxY, int boxW, int boxH, int brightness_adjust, double contrast_adjust,
					int &xRelative);

	void image_yuv_channelY(const Image& img);
};


#endif
