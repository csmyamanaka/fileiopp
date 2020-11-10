/*
  Bitmap File IO ++ header file
  bmpfileiopp.h
  M. Yamanaka
  email: myamanaka@live.com
  website: http://www.csmyamanaka.com
  license: MIT (See included "LICENSE" file for details)
*/

#pragma once

#include "varbyterw.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Bitmap Information Struct
  This struct contains information that is required to interpret bitmap files assuming no compression.
  The attributes from left to right are:
    h   ... height
    w   ... width
    c   ... number of channels (e.g. 1 for grayscale, 3 for RGB)
    fn  ... file name
*/
typedef struct BMPIS{int h, w, c; const char* fn;} BMPIS;

/*
  The functions below were written using wikipedia as a reference for the bitmap file structure:
  <https://en.wikipedia.org/wiki/BMP_file_format>
  Please see the implementation file "bmpfileiopp.c" for more details
*/

/*
  Read Bitmap
  The details such as width, height, number of channels and the image data are extracted
  and stored into objects referenced by the arguments to this function.
  The arguments from left to right are:
    BMPIS*  ... Bitmap information struct pointer
    char**    ... the address of a char (effectively byte) array will accept the image data of the bitmap
*/
int readBMP(BMPIS*, char**);

/*
  Write Bitmap
  A bitmap file is created using details provided by the objects referenced by the arguments to this function.
  The arguments from left to right are:
    BMPIS*  ... Bitmap information struct pointer with all components (h, w, c, fn) defined
    char**    ... the image data that will be written onto the bitmap file
*/
int writeBMP(BMPIS, char*);


