/*
 * functions.cpp
 *
 *  Created on: 8 May 2015
 *      Author: niko
 */

#include "functions.h"

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

//CONVERTS TO VALUE THAT CAN BE OUTPUT TO AN IMAGE, VLAUE BETWEEN 0 AND 255
byte rgb_to_v_int(const Pixel& in){	

	int value=max( (max( (int)in.red(), (int)in.green() )), ((int)in.blue()) );
	return (byte)value;

}

//converts rgb to HSV and returns V; value between 0 and 1
double rgb_to_v(const Pixel& in){
	
	int m=max( (max( (int)in.red(), (int)in.green() )), ((int)in.blue()) );
	double value=m/255.0;
	return value;

}

// CONVERTS TO HSL AND RETURNS L CHANNEL
byte rgb_to_l(const Pixel& in){
	int tmin=min( (min( (int)in.red(), (int)in.green() )), ((int)in.blue()) );
	int tmax=max( (max( (int)in.red(), (int)in.green() )), ((int)in.blue()) );
	return (byte)((tmin+tmax)/2);
}

//finds a particular color in the image
void find_color(const Pixel& color, const int& treshold, const Image& input, Image& output){
	for(int y=0; y<input.height(); y++){
		for(int x=0; x<input.width(); x++){
			
			int distance=sqrt(pow(((char)(color.red()-input[y][x].red())) , 2) + pow(((char)(color.green()-input[y][x].green())) , 2) 
				+ pow(((char)(color.blue()-input[y][x].blue())), 2));
			if(distance<=treshold){
				output[y][x].set_intensity(WHITE);
			}
			else{
				output[y][x].set_intensity(BLACK);
			}
		}
	}
}

//converts image to another color space
void convert(const Image& input, Image& output){
	int y,x, sum=0;

	for( y=0; y<input.height(); y++){
		for( x=0; x<input.width(); x++){
			
			//byte value=rgb_to_v_int(input[y][x]);
			//output[y][x].set_intensity(value);
			
			
		
			//double value=rgb_to_v(input[y][x]);
			//if(value<TRESHOLD) output[y][x].set_intensity(WHITE);
			//else output[y][x].set_intensity(BLACK);

			byte value=rgb_to_l(input[y][x]);
			//output[y][x].set_intensity(value);
			if(abs(COLOR-value)<TRESHOLD) output[y][x].set_intensity(WHITE);
			else output[y][x].set_intensity(BLACK);
			//sum=sum+value;
			//cout<<(int)value<<endl;
		}
	}
	//cout<<"average="<<sum/(y*x)<<endl;

}

//void treshold(const int& tresh, const Image& input, Image& output){}