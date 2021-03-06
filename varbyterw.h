/*
  Variable-Byte Data Reader/Writer header file
  varbyterw.h
  M. Yamanaka
  email: myamanaka@live.com
  website: http://www.csmyamanaka.com
  License: MIT (See included "LICENSE" file for details)
*/

#pragma once

#include <stdlib.h>

/*
  Write Data to Char Array
  "char" is a stand-in for byte because C doesn't have a byte type at least on the compiler that I am using at this time (GCC 9.3.0).
  Therefore, this function writes the byte representation of a given input data onto a char (byte) array.
  This can be done in either endian format controlled by the last argument of this function.
  The arguments from left to right are:
    void*   ... input data
    char* ... destination char array
    int   ... number of bytes
    int   ... endian-ness, 0 for little-endian, 1 for big-endian
  The return value is 0 but eventually, I would like to implement error codes.
*/
int wDataToChar(void*, char*, int, int);

/*
  Read Data from Char Array
  Again, "char" is just byte.
  This function reads a series of bytes in either endian form and extracts the data and interprets it as a given variable..
  The arguments from left to right are:
    char* ... byte data
    void*   ... destination variable
    int   ... number of bytes to interpret
    int   ... endian-ness, 0 for little, 1 for big
  A return value is also tentatively 0 but likewise with the aforementioned plan.
*/
int rDataFromChar(char*, void*, int, int);

