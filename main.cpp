/*
 * main.cpp
 *
 *  Created on: 3 May 2015
 *      Author: niko
 */
#include "jpeg/jpeg.h"
#include <assert.h>
#include <iostream>
#include <math.h>
#include "pixel/pixel.hpp"
#include "image/image.hpp"
#include "process_loci/process_loci.cpp"

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

int main(int argc, char *argv[])
{ 

	double blur[3][3]={{1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}};

	assert(argc >= 3 && "Expected input file name and output file name as CLI argument!!");
    int height, width, components_count;
    unsigned char ** image_in;
    unsigned char ** image_out;

    //decompressing the image; image variable now contains the information for the image
    if(jpeg_check_file(argv[1])){
        jpeg_decode(argv[1], height, width, components_count, image_in);
    }

    else {
        cerr << "Unrecognized file type!" << endl;
        cerr << "Terminating now!" << endl;
        return 1;
    }

    //cout<<"components count is "<<components_count<<endl;
    //cout<<"height "<<height<<endl;
    //cout<<"width "<<width<<endl;

    //Image inimage (height, width), outimage(height, width);
    Image* inptr = new Image(height, width);
    Image &inimage=*inptr;

    // extract the components
    array_to_image(image_in, inimage);

    //Free memory space
    for(int i = 0 ; i < height ; i++) {
        delete[] image_in[i];
    }
    delete[] image_in;

    //Create output object
    Image* outptr=new Image(height, width);
    Image &outimage=*outptr;

////
    Pixel dark;//= new Pixel((char)255, (char)255, (char)255);
    dark.set_rgb(0,0,0);

    Pixel treshold;
    treshold.set_rgb(10,10,20);

    Process_loci processor;
    //processor.find_center(inimage, white, tresh_5, 675, 334, 100, 50);
    
    //for s1, s2, s3
    int irisX;
    /*processor.find_center(inimage, dark, treshold, 700, 328, 100, 50,
                        0, 10.0, irisX);*/

    //For vid1
    //processor.find_center(inimage, dark, treshold, 640, 235, 80, 45,
    //                    30, 10.0, irisX);

    //For vid2
    //processor.find_center(inimage, dark, treshold, 486, 271, 90, 50,
    //                    30, 10.0, irisX);

    //processor.find_center(inimage, dark, treshold, 545, 217, 70, 50,
    //                30, 10.0, irisX);

    processor.image_yuv_channelY(inimage);
////

    //apply the filter
    apply_filter(blur, inimage, outimage);
    
    
    delete inptr;

    //initialize output array
    image_out=new unsigned char* [height];
    for(int y=0; y<height; y++){
       	image_out[y] = new unsigned char [width * components_count];
    }

    //convert the output image in appropriate type
    image_to_array(outimage, image_out);

    //delete outptr;

    // encode into intended file format
    int output_file_type = get_file_type(argv[2]);
    switch(output_file_type) {
        case FILE_TYPE_JPEG:
        	jpeg_encode(argv[2], height, width, components_count, image_out);
        break;

        default:
        case FILE_TYPE_ERR:
        	cout << "Unkown output file type! Using default of jpeg" << endl;
        	jpeg_encode(argv[2], height, width, components_count, image_out);
        break;
    }

    //Free the memory space
    for(int i = 0 ; i < height ; i++) {
    	delete[] image_out[i];
    }
    delete[] image_out;

    return 0;
}


//****************************************************************************************************
//										FUNCTION DEFINITIONS
//****************************************************************************************************

int get_file_type(const char * filename){
    int i;
    for(i = 0 ; filename[i] ; i++);
    i--;
    if((filename[i-3] == 'j' && filename[i-2] == 'p' && filename[i-1] == 'e' && filename[i] == 'g') ||
        (filename[i-2] == 'j' && filename[i-1] == 'p' && filename[i] == 'g')){
        return FILE_TYPE_JPEG;
    }
    else{
        return FILE_TYPE_ERR;
    }
}

//****takes a filter, input and output image and coordinates of a pixel
//****applies the filter to the input pixel and outputs it in the output image
void convolute(double filter[FIL_DIM][FIL_DIM], const Image& input, const int y, const int x, Image& output){

	double red=0, green=0, blue=0;
	for(int i=0; i<FIL_DIM; i++){
		for(int j=0; j<FIL_DIM; j++){
			red+=filter[j][i]*(double)(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].red());
			green+=filter[j][i]*(double)(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].green());
			blue+=filter[j][i]*(double)(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].blue());
		}
	}
	//N.B. IF APPLYING SOBEL FILTER OR ANY OTHER FILTER WITH NEGATIVE VALUES, FIRST TAKE THE ABS OF ALL COMPONENTS
	//AND THEN DO set_rgb()

	output[y][x].set_rgb((unsigned char)red, (unsigned char)green, (unsigned char)blue);
	//cout<<red<<" "<<green<<" "<<blue<<endl;
	//cout<<output[y][x]<<endl;
}

//******applies filter to an image using the convolute function
void apply_filter(double filter[FIL_DIM][FIL_DIM], const Image& input, Image& output){
	for(int y=0; y<input.height(); y++){
		for(int x=0; x<input.width(); x++){
			if(x<(FIL_DIM/2) || y<(FIL_DIM/2) || x>(input.width()-(FIL_DIM/2)-1) || y>(input.height()-(FIL_DIM/2)-1) ){
				output[y][x].set_to_pix(input[y][x]);
			}
			else{
				convolute(filter, input, y, x, output);
			}
		}
	}
}

void apply_filter(int filter[FIL_DIM][FIL_DIM], const Image& input, Image& output){
	for(int y=0; y<input.height(); y++){
		for(int x=0; x<input.width(); x++){
			if(x<(FIL_DIM/2) || y<(FIL_DIM/2) || x>(input.width()-(FIL_DIM/2)-1) || y>(input.height()-(FIL_DIM/2)-1) ){
				output[y][x].set_to_pix(input[y][x]);
			}
			else{
				convolute(filter, input, y, x, output);
			}
		}
	}
}

void convolute(int filter[FIL_DIM][FIL_DIM], const Image& input, const int y, const int x, Image& output){
	int red=0, green=0, blue=0;
	for(int i=0; i<FIL_DIM; i++){
		for(int j=0; j<FIL_DIM; j++){
			red+=filter[j][i]*(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].red());
			green+=filter[j][i]*(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].green());
			blue+=filter[j][i]*(input[y-(FIL_DIM/2)+j][x -(FIL_DIM/2)+i].blue());
		}
	}
	//N.B. IF APPLYING SOBEL FILTER OR ANY OTHER FILTER WITH NEGATIVE VALUES, FIRST TAKE THE ABS OF ALL COMPONENTS
	//AND THEN DO set_rgb()

	output[y][x].set_rgb((unsigned char)red, (unsigned char)green, (unsigned char)blue);
	//cout<<red<<" "<<green<<" "<<blue<<endl;
	//cout<<output[y][x]<<endl;
}


void array_to_image(unsigned char** in, Image& out){
	int components_count=3;		//for RGB
	for(int y = 0 ; y < out.height() ; y++) {
        for(int x = 0 ; x < out.width() ; x++) {
        	out[y][x] = Pixel(in[y][components_count*x], in[y][components_count*x+1], in[y][components_count*x+2]);
        }
    }
}


void image_to_array(Image& in, unsigned char** out){
	int height=in.height(), width=in.width(), components_count=3;
    for(int y=0; y<height; y++){
    	for(int x=0; x<width; x++){
    		out [y][x*components_count]=in[y][x].red();
    		out [y][x*components_count+1]=in[y][x].green();
    		out [y][x*components_count+2]=in[y][x].blue();
    	}
    }

}

void find_color(const Pixel& color, const int& treshold, const Image& input, Image& output){
	for(int y=0; y<input.height(); y++){
		for(int x=0; x<input.width(); x++){
			int distance=sqrt(pow(((char)(color.red()-input[y][x].red())) , 2) + pow(((char)(color.green()-input[y][x].green())) , 2) +pow(((char)(color.blue()-input[y][x].blue())), 2));
			if(distance<=treshold){
				output[y][x].set_intensity(WHITE);
			}
			else{
				output[y][x].set_intensity(BLACK);
			}
		}
}
}
