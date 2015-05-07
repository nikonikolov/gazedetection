#Makefile for Gaze Detector algorithm written in C++
#Requires libjpeg and libmagic

#Files to compile
SOURCES = file/file.cpp jpeg/jpeg.cpp image/image.cpp pixel/pixel.cpp main.cpp
#Output file
OUTPUT = ./main
#Libraries to include by absolute path. Not in use because flags can be used
LIBS =  #/usr/lib/x86_64-linux-gnu/libjpeg.so /usr/lib/x86_64-linux-gnu/libmagic.so
#Flags including libjpeg and libmagic
FLAGS = -std=c++11 -ljpeg -lmagic


all: $(OUTPUT)
	
$(OUTPUT) : $(SOURCES)
	rm -f main
	g++ -o $(OUTPUT) $(SOURCES) $(LIBS) $(FLAGS)
