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
#include "pixel/pixel.h"
#include "image/image.h"
#include "process_loci/process_loci.h"
#include "functions/functions.h"

typedef unsigned char byte;

using std::cin;
using std::cout;
using std::cerr;
using std::endl;


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

//***********************************END*******************************************************
