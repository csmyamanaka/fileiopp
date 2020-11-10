/*
  Variable-Byte Reader/Writer implemetation file
  varbyterw.c
  M. Yamanaka
  email: myamanaka@live.com
  website: csmyamanaka.com
  license: MIT (See included "LICENSE" file for details)
*/

#include "varbyterw.h"


int wDataToChar(void* ipt, char* dst, int b, int e){
  /*
    ipt ... input data
    dst ... destination array
    b ... number of bytes
    e ... endian-ness. 0 indicates little-endian and 1, big-endian
  */
  
  /*
    I could be wrong but I'm pretty sure gcc (or at least the version that I'm using) stores variables as big-endian
    I came to this conclusion because I tested out the following code:
    
    int main(){
      int n = 65;
      int* pn = &n;
      char* pcn = (char*)pn;
      if(*pcn == '\0' && *(pcn + 3) == 'A') printf("big endian\n");
      else if(*pcn == 'A' && *(pcn + 3) == '\0') printf("little endian\n");
      else printf("something probably went wrong\n");
      return 0;
    }

    and got the second print statement.
    I don't know if this varies from compiler to compiler.
    If it helps, I tested this on Void Linux using GCC 9.3.0
  */
  
  if(e != 0 && e != 1) return -1;
  
  /*
    Assuming that the variables are indeed stored in little-endian format,
    if match the indices as the bytes are being written,
    the resulting byte array should also be little-endian.
    If one of the indices is reversed, the result should be big-endian.

    The for-loop below may look a little convoluted but it should handle both cases:
    i.e. when "e" = 0, "i" and "j" should match whereas "i" would count up from 0 to "b" - 1
    and "j" would count down from "b" - 1 to 0 when "e" = 1.
    It saves me from having to write two for loops or an if statement in the loop
    thereby making the code shorter suckless style
  */
  for(int i = 0, j = (b - 1)*e; i < b; i++, j += 1 - 2*e) dst[i] = *((char*)ipt + j);
  return 0;
}

int rDataFromChar(char* ipt, void* dst, int b, int e){
  /*
    ipt ... input array
    dst ... destination data
    b ... number of bytes to interpret
    e ... endian-ness, 0 for little-endian and 1 for big-endian
  */
  
  if(e != 0 && e != 1) return -1;
  for(int i = 0, j = (b - 1)*e; i < b; i++, j += 1 - 2*e) *((char*)dst + i) = ipt[i];
  return 0;
}

