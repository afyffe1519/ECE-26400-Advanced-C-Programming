#ifndef BIT_H
#define BIT_H
#include <stdio.h>
#include <stdlib.h>

int write(FILE * fptr, unsigned char bit, unsigned char * bit1, unsigned char * bit2);
int pad(FILE * fptr, unsigned char * bit1, unsigned char * bit2);
int read(FILE * fptr, unsigned char * bit, unsigned char * bit1, unsigned char * byte1);

#endif

