/*
 * test.cpp
 *
 *  Created on: 6 May 2015
 *      Author: niko
 */
#include<iostream>
#include "image/image.hpp"
#include "pixel/pixel.hpp"
//#include "testclass.hpp"
using namespace std;

int main(){

	Pixel a[10];
	//testclass i(2,2);
	/*cout<<"the address of i[0][0] is "<<&i[0][0]<<endl;
	cout<<"the address of i[0][1] is "<<&i[0][1]<<endl;
	cout<<"the address of i[1][0] is "<<&i[1][0]<<endl;
	cout<<"the address of i[1][1] is "<<&i[1][1]<<endl;
	i[0][0]=10;*/
	//i[0][0].set_red(10);
	//cout<<"the value of red in i[0][0] is "<<i[0][0].red()<<endl;
	//cout<<"the value in i[0][0] is "<<i[0][0]<<endl;
	a[0]=Pixel(20,20,20);
	cout<<"a[0] red is"<<(int)a[0].red()<<" "<<(int)a[0].green()<<" "<<(int)a[0].blue()<<endl;
	Pixel b(70, 50, 60);
	cout<<"b is"<<(int)b.red()<<" "<<(int)b.green()<<" "<<(int)b.blue()<<endl;

	Image c(2,2);
	c[0][0]=Pixel(20, 30, 40);
	//cout<<"c[1][1] is"<<(int)c[1][1].red()<<" "<<(int)c[1][1].green()<<" "<<(int)c[1][1].blue()<<endl;
	cout<<"c[1][1] is"<<c[1][1]<<endl;
	c[1][1].set_rgb(50,60,70);
	//cout<<"c[1][1] is"<<(int)c[1][1].red()<<" "<<(int)c[1][1].green()<<" "<<(int)c[1][1].blue()<<endl;
	cout<<"c[1][1] is"<<c[1][1]<<endl;
	return 0;
}



