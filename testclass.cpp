/*
 * testclass.cpp
 *
 *  Created on: 6 May 2015
 *      Author: niko
 */
#include "testclass.hpp"

	testclass::testclass (int height_in, int width_in){
		iheight=height_in;
		iwidth=width_in;
		ptr=new int* [iheight];
		for(int i=0; i<iheight; i++){
			ptr[i]= new int [iwidth];
		}

	}

	testclass::~testclass(){
		for(int i=0; i<iheight; i++){
			delete[] ptr[i];
		}
		delete[] ptr;
	}

	int testclass::height() const{
		return iheight;
	}

	int testclass::width() const{
		return iwidth;
	}

	int* testclass::operator[](int index){
		return ptr[index];
	}




