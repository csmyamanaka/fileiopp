/*
  Bitmap File IO ++ Implementation File
  "bmpfileiopp.c"
  M. Yamanaka
  email: myamanaka@live.com
  website: csmyamanaka.com
  license: MIT (See included "LICENSE" file for details)
*/

/*
  According to the wikipedia page (full URL in the header file), the bitmap header requires:
  - 2 bytes for the BMP file signature
  - 4 bytes for the file size
  - 4 bytes for some reason
  - 4 bytes that points to the location of the actual data
  - 4 bytes just to say 40?
  - 4 bytes for the image width
  - 4 bytes for the image height
  - 2 bytes for the image plane (apparently we can just set this to 1)??
  - 2 bytes for bits per pixel 8 bits for 0-255 so for RGB, it should be 24 bits
  - 4 bytes for the compression, pretty sure we don't have to do any compression so probably just set this to 0
  - 4 bytes for idkwtf. apparently i can set this to 0 as well if we set the compression to 0
  - 4 bytes for pixels per meter for x. idk 1000 might be a good number. that's 1 pixel = 1 mm
  - 4 bytes for pixels per meter for y. same here, probably just 1000
  - 4 bytes for "Colors Used". It looks like I can set this to 0
  - 4 bytes for "Important Colors"  it says we can just set this to 0

  According to "Example 1" on the wikipedia page, it seems like I don't need the color table section
  or at least it is outisde the scope at least for now to have to handle any of that.

  Whew that was a lot so that's 14 bytes for the first section and 40 bytes for the second so the 54th bytes is where the image data begins.
  
  The total file size is therefore 54 bytes + number of elements in the data array
*/

#include "bmpfileiopp.h"

int readBMP(BMPIS* bfi, char** bd){
  /*
    fn ... bmp file name
    bfi ... bitmap file information
    bd ... bitmap image data
  */
  
  FILE* imf = fopen(bfi->fn, "r");
  char rb[64]; //read buffer
  
  //check if the file in question is indeed a bitmap file by checking the header
  fread(rb, sizeof(char), 2, imf);
  if(rb[0] != 'B' || rb[1] != 'M') return -1;
  
  int details[4]; //temporary storage for important variables: image date location, width, height, and number of cnannels
  int ds[4] = {4, 4, 4, 2}; //the byte sizes of each 
  int adv[7] = {8, 4, 4, 4, 4, 2, 2}; //read sizes. Some reads will contain the above variables. Others are ignored.
  for(int i = 0, di = 0; i < 7; i++){
    fread(rb, sizeof(char), adv[i], imf);
    if(i == 1|| i == 3 || i == 4 || i == 6){
      rDataFromChar(rb, details + di, ds[di], 0);
      di++;
    }
  }
  
  bfi->w = details[1];
  bfi->h = details[2];
  bfi->c = details[3]/8;
  
  //the file pointer is at byte 30 at this point so we need bring this to details[0]
  fread(rb, sizeof(char), details[0] - 30, imf);

  //the actual data size (assuming there's no compression) is width*height*channels
  int dsz = (bfi->w)*(bfi->h)*(bfi->c); //data size
  *bd = (char*)malloc(sizeof(char)*dsz);
  fread(*bd, sizeof(char), dsz, imf);
  fclose(imf);
  return 0;
}

int writeBMP(BMPIS bfi, char* bd){
  /*
    bfi: bitmap file information
    bd: bitmap data array
  */
  
  //the size of the data array whould be height x width x number of channels
  int datsz = bfi.h*bfi.w*bfi.c;
  
  //create an array of bytes that represents the file
  char* file_contents = (char*)malloc(sizeof(char)*(54 + datsz));

  //but starting with byte 54, the entirety of array a1 is copied onto the file contents
  for(int i = 0; i < datsz; i++) file_contents[i + 54] = bd[i];

  //for the BMP signature, set byte 0 to 'B' and byte 1 to 'M' as indicated by ece.ualberta.ca
  file_contents[0] = 'B';
  file_contents[1] = 'M';
  
  int cb = 2; //the current byte position is 2 after having read 'B' and 'M'
  int details[14] = {54 + datsz, 0, 54, 40, bfi.w, bfi.h, 1, bfi.c*8, 0, 0, 1000, 1000, 0, 0};
  int bsz[14] = {4, 4, 4, 4, 4, 4, 2, 2, 4, 4, 4, 4, 4, 4};
  
  for(int i = 0; i < 14; cb += bsz[i++]) wDataToChar(details + i, file_contents + cb, bsz[i], 0);

  //Write the char array into the output file
  FILE* bmpfile = fopen(bfi.fn, "w");
  for(int i = 0; i < 54 + datsz; i++) fputc(file_contents[i], bmpfile);
  fclose(bmpfile);
  
  //deallocate memory
  free(file_contents);
  return 0;
}


