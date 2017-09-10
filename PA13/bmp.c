#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) {
	BMPImage * image = malloc(sizeof(BMPImage));
 	fread(&(image -> header), sizeof(BMPHeader), 1, fp);
	if((image -> header).height_px < 0)
	{
		image -> norm_height = (image -> header).height_px * -1;
	}
	else
	{
		image -> norm_height = (image -> header).height_px;
	}
	image -> pixels = malloc(image -> norm_height * sizeof(Pixel *));
	for(int i = 0; i < image -> norm_height; i++)
	{
		image -> pixels[i] = malloc((image -> header.width_px) * sizeof(Pixel));
		for(int j = 0; j < image -> header.width_px; j++)
		{
			fread( & image -> pixels[i][j], sizeof(Pixel), 1, fp);
		}
	}
	return image;
}

void freeImage(BMPImage * image) {
	
	if(image != NULL)
	{
		for(int i = 0; i < image -> norm_height; i++)
		{
			free(image -> pixels[i]);
		}

		free(image -> pixels);
	}
	
	free(image);

}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) {

	fwrite(& (image -> header), sizeof(BMPHeader), 1, fp);
	for(int i = 0; i < image -> norm_height; i++)
	{
		for(int j = 0; j < image -> header.width_px; j++)
		{
			fwrite( & image -> pixels[i][j], sizeof(Pixel), 1, fp);
		}
	}
	return;

}
#endif
