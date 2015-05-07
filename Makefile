SOURCES = file/file.cpp jpeg/jpeg.cpp image/image.cpp pixel/pixel.cpp main.cpp
OUTPUT = ./main
LIBS = /usr/lib/x86_64-linux-gnu/libjpeg.so.8 /usr/lib/x86_64-linux-gnu/libmagic.so
FLAGS = -std=c++11


all: $(OUTPUT)
	
$(OUTPUT) : $(SOURCES)
	rm -f main
	g++ -o $(OUTPUT) $(SOURCES) $(LIBS) $(FLAGS)
