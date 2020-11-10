/*
  File IO ++ teser/example file
  "tester.c"
  M. Yamanaka
  email: myamanaka@live.com
  website: csmyamanaka.com
  license: MIT (See included "LICENSE" file for details)
*/

#include "bmpfileiopp.h"

int main(){

  /*
    This example creates a simple bitmap file with a very generic pattern and writes it to a file.
    This file is then read, and its dimensions and number of channels are printed to stdout.
  */
  
  //write
  int n = 3; //number of channels
  BMPIS e1 = {400, 600, n, "example1.bmp"}; //example 1
  char* dE1 = (char*)malloc(sizeof(char)*400*600*n); //data for e1

  for(int i = 0; i < 400*600*n; i++){
    if(i < 200*600*n) dE1[i] = (char)255;
    else dE1[i] = (char)0;
  }
  writeBMP(e1, dE1);

  //read
  BMPIS e2 = {0, 0, 0, "example1.bmp"};
  char* dE2;
  readBMP(&e2, &dE2);
  printf("width: %d, height: %d, number of channels: %d\n", e2.w, e2.h, e2.c);

  free(dE1);
  free(dE2);
  return 0;
}
