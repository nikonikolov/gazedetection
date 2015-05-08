/*
*	Process file by me
*
*/

#include "process_loci.h"

	//Test function to test color counting
	bool Process_loci::is_match(Pixel& pixel, Pixel color, Pixel treshold) {
	    int k = (int) pixel.red() - (int) color.red();
	    if (abs(k) > (int) treshold.red()) return false;

	    k = (int) pixel.green() - (int) color.green();
	    if (abs(k) > (int) treshold.green()) return false;

	    k = (int) pixel.blue() - (int) color.blue();
	    if (abs(k) > (int) treshold.blue()) return false;

	    //cout << "is_match finised" << endl;
	    return true;
	}

	//Finds the center of points with a given color in a given area of the image
	void Process_loci::find_center(const Image& input, Pixel color, Pixel treshold,
									int boxX, int boxY, int boxW, int boxH, int brightness_adjust, double contrast_adjust,
									int &xRelative) {

		//Using unnecessary long variables
		unsigned long count = 0;	    
	    unsigned long long averageX = 0;
	    unsigned long long averageY = 0;
	    xRelative = -1; //Default output if no eye found

	    //Perfect for eye
		brightness(input, brightness_adjust);
		contrast(input, contrast_adjust);

		for (int y = boxY; y < boxY + boxH; y++) {
			for (int x = boxX; x < boxX + boxW; x++) {
				if (is_match(input[y][x], color, treshold)) {
	                count ++;
	                averageX += x;
	                averageY += y;

	                //input[y][x].set_rgb(0,0,255);	//For marking every pixel that matches
	            }

	            //input[y][x].set_rgb(0,0,255);	//For drawing a box around search area
			}			
		}
		
		//If any match has been found
		if (count > 0) {
		    averageX /= count;
		    averageY /= count;

		    xRelative = averageX - boxX;
		    int yRelative = averageY - boxY;

		    int xMapped = map_value(xRelative, 32, 52, 50, 1200);
		    int yMapped = map_value(yRelative, 15, 26, 50, 650);

		    cout << "x: " << xRelative << " y: " << yRelative << endl;

		    Pixel green;
		    green.set_rgb(0,255,0);
		    //int mapped = map_value(xRelative, 19, 63, 50, 1200);
		    fill_rectangle(input, xMapped, yMapped, 20, green);
			

		} 

		//cout << "Relative bounds X: " << xRelative << endl;
	}

//
//Helper functions to make the matching procedure easier
//
	//Helper for brightness function
	unsigned char Process_loci::addAndBound(unsigned char orig, int mod_brightness) {
		int o = (int)orig + mod_brightness;
		if (o < 0) return 0;
		if (o > 255) return 255;
		return o;
	}

	//Setting the brightness (max 255, minimum -255)
	void Process_loci::brightness(const Image& input, int mod_brightness) {
		for(int y=0; y<input.height(); y++){
	        for(int x=0; x<input.width(); x++){
	        	input[y][x].set_red(addAndBound(input[y][x].red(), mod_brightness));
	        	input[y][x].set_green(addAndBound(input[y][x].green(), mod_brightness));
	        	input[y][x].set_blue(addAndBound(input[y][x].blue(), mod_brightness));
	        }
	    }
	}

	//Helper for contrasting the image
	unsigned char Process_loci::multipAndBound(unsigned char orig, double mod_contrast) {
		double o = (double)orig - 127;
		o *= mod_contrast;
		o += 127;

		if (o < 0) return 0;
		if (o > 255) return 255;
		return (unsigned char)o;
	}

	//Contrast image with a (double) as multiplier
	void Process_loci::contrast(const Image& input, double mod_contrast) {
		for(int y=0; y<input.height(); y++){
	        for(int x=0; x<input.width(); x++){
	        	input[y][x].set_red(multipAndBound(input[y][x].red(), mod_contrast));
	        	input[y][x].set_green(multipAndBound(input[y][x].green(), mod_contrast));
	        	input[y][x].set_blue(multipAndBound(input[y][x].blue(), mod_contrast));
	        }
	    }
	}

	//Fills rectangle with given color
	void Process_loci::fill_rectangle(const Image& input, int centerX, int centerY, int dimension, Pixel color) {
	    int halfDimension = dimension / 2;
	    for (int i = centerY - halfDimension ; i <= centerY + halfDimension; i++) {
	    	for (int j = centerX - halfDimension ; j < centerX + halfDimension; j++) {
	    		input[i][j].set_to_pix(color);
	    	}
	    }
	}

	int Process_loci::map_value(int value, int inMin, int inMax, int outMin, int outMax) {
		
		int inDiff = inMax - inMin;
		int outDiff = outMax - outMin;
		double mapped = (double)outDiff / (double)inDiff;

		value -= inMin;		
		mapped *= (double)value;
		mapped += (double)outMin;

		return (int)mapped;
	}

	void Process_loci::RGB_to_YUV(double &Y, double &U, double &V, const double R, const double G, const double B) {
		Y =  0.257 * R + 0.504 * G + 0.098 * B +  16;
		U = -0.148 * R - 0.291 * G + 0.439 * B + 128;
		V =  0.439 * R - 0.368 * G - 0.071 * B + 128;
	}

	void Process_loci::image_yuv_channelY(const Image& img) {
		for (int y = 0; y < img.height(); y++) {
			for (int x = 0; x < img.width(); x++) {
				double new_y, new_u, new_v;

				RGB_to_YUV(new_y, new_u, new_v, (double)img[y][x].red(), (double)img[y][x].green(), (double)img[y][x].blue());

				unsigned char new_intensity = (unsigned char)new_y;
				img[y][x].set_intensity(new_intensity);
			}
		}
	}

