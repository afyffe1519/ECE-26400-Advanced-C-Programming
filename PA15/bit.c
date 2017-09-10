#include "bit.h"

int write(FILE * fptr, unsigned char bit, unsigned char * bit1, unsigned char * bit2)
{
	int return_write;
	if((* bit1) == 0)
	{
		*bit2 = 0;
	}

	unsigned char temp = bit << (7 - (*bit1));
	*bit2 |= temp;
	int temp2 = 0;
	if((*bit1) == 7)
	{
		return_write = fwrite(bit2, sizeof(unsigned char), 1, fptr);
		if(return_write == 1)
		{
			temp2 = 1;
		}
		else
		{
			temp2 = -1;
		}
	}
	*bit1 = ((*bit1) + 1) % 8;
	return temp2;
}

int pad(FILE * fptr, unsigned char * bit1, unsigned char * bit2)
{
	int return_value;
	while((*bit1) != 0)
	{
		return_value = write(fptr, 0, bit1, bit2);
		if(return_value == -1)
		{
			return -1;
		}
	}
	return return_value;
}

int read(FILE * fptr, unsigned char * bit, unsigned char * bit1, unsigned char * byte1)
{
	int temp = 1;
	if((* bit1) == 0)
	{
		temp = fread(byte1, sizeof(unsigned char), 1, fptr);
	}
	if(temp != 1)
	{
		return -1;
	}
	unsigned char temp2 = (*byte1) >> (7 - (*bit1));
	temp2 = temp2 & 0X01;
	*bit1 = ((* bit1) + 1) % 8;
	*bit = temp2;
	return 1;
}
