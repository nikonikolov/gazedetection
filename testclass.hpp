/*
 * testclass.hpp
 *
 *  Created on: 6 May 2015
 *      Author: niko
 */
class testclass{

private:

	int** ptr;
	int iheight;
	int iwidth;

public:
	testclass (int height_in, int width_in);
	~testclass();
	int height() const;
	int width() const;
	int* operator[](int index);

};




