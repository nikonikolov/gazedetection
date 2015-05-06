/*
 * file.cpp
 *
 *  Created on: 3 May 2015
 *      Author: niko
 */
#include "file.h"

bool file_check_type(const char * filename, const char * type) {
    int i;
    magic_t cookie = magic_open(MAGIC_NONE);

    //The function magic_open() creates a magic cookie pointer and returns it.
    //It returns NULL if	there was an error allocating the magic	cookie.	The
    //flags argument specifies how the other magic functions should behave:
    //MAGIC_NONE	No	special	handling.

    if( magic_error(cookie)) {
    	//The magic_error() function	returns	a textual explanation of the last
    	//error, or NULL if there was no error.
        printf("An error occured:\n");
        printf("%s\n", magic_error(cookie));
        return false;
    }
    magic_load(cookie, NULL);
    const char * des = magic_file(cookie, filename);
    //The magic_file() function returns a textual description of	the contents
    //of the filename argument, or NULL if an error occurred.


    for(i = 0 ; type[i] && des[i] ; i++) {
    	// int tolower(int c) converts a given letter to lowercase
        if(tolower(des[i]) != tolower(type[i])) {
            magic_close(cookie);
            printf("File extension not right \n");
            return false;
        }
    }
    magic_close(cookie);
    //The magic_close() function closes the magic(5) database and deallocates
    //any resources used.

    return i == strlen(type);
}

//for more info about libmagic http://www.freebsd.org/cgi/man.cgi?query=libmagic&sektion=3&manpath=FreeBSD+7.0-RELEASE

