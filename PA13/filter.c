#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image) {
	Pixel temp, one, two, three, four, five, six, seven, eight;
	int i;
	int j;
	BMPImage * image2 = malloc(sizeof(BMPImage));
	image2 -> header = image -> header;
	image2 -> norm_height = abs(image -> header.height_px);
	image2 -> pixels = malloc(sizeof(Pixel *) * (image2 -> norm_height));
	for(i = 0; i < (image -> norm_height); i++)
	{
		image2 -> pixels[i] = malloc(sizeof(Pixel) * image2 -> header.width_px);
		for(j = 0; j < (image -> header).width_px; j++)
		{
			one = currentPixel(image, i - 1, j - 1);
			two = currentPixel(image, i - 1, j);
			three = currentPixel(image, i - 1, j + 1);
			four = currentPixel(image, i, j - 1);
			temp = currentPixel(image, i, j);
			five = currentPixel(image, i, j + 1);
			six = currentPixel(image, i + 1, j - 1);
			seven = currentPixel(image, i + 1, j);
			eight = currentPixel(image, i + 1, j + 1);

			image2 -> pixels[i][j].blue = (temp.blue + one.blue + two.blue + three.blue + four.blue + five.blue + six.blue + seven.blue + eight.blue) / 9;
			image2 -> pixels[i][j].red = (temp.red + one.red + two.red + three.red + four.red + five.red + six.red + seven.red + eight.red) / 9;
			image2 -> pixels[i][j].green = (temp.green + one.green + two.green + three.green + four.green + five.green + six.green + seven.green + eight.green) / 9;
			image2 -> pixels[i][j].alpha = (temp.alpha + one.alpha + two.alpha + three.alpha + four.alpha + five.alpha + six.alpha + seven.alpha + eight.alpha) / 9;
		}
	}

	return image2;

}
#endif

Pixel currentPixel(BMPImage * image, int i, int j)
{
	if(i < 0)
	{
		i = 0;
	}
	if(j < 0)
	{
		j = 0;
	}
	if(i >= (image -> norm_height))
	{
		i = image -> norm_height - 1;
	}
	if(j >= image -> header.width_px)
	{
		j = image -> header.width_px - 1;
	}
	return image -> pixels[i][j];
}
// EXTRA CREDIT START
BMPImage * apply(BMPImage * image, BoxFilter f) {
	
//	Pixel temp, one, two, three, four, five, six, seven, eight;
//	int i;
//	int j;
//	for(i = 0; i < (image -> norm_height); i++)
//	{
///		for(j = 0; j < (image -> header).width_px; j++)
//		{
//			one = currentPixel(image, i - 1, j - 1);
//			two = currentPixel(image, i - 1, j);
//			three = currentPixel(image, i - 1, j + 1);
//			four = currentPixel(image, i, j - 1);
//			temp = currentPixel(image, i, j);
//			five = currentPixel(image, i, j + 1);
//			six = currentPixel(image, i + 1, j - 1);
//			seven = currentPixel(image, i + 1, j);
//			eight = currentPixel(image, i + 1, j + 1);
//
//			image -> pixels[i][j].blue = (temp.blue + one.blue + two.blue + three.blue + four.blue + five.blue + six.blue + seven.blue + eight.blue) / (f-> norm);
//			image -> pixels[i][j].red = (temp.red + one.red + two.red + three.red + four.red + five.red + six.red + seven.red + eight.red) / (f -> norm);
//			image -> pixels[i][j].green = (temp.green + one.green + two.green + three.green + four.green + five.green + six.green + seven.green + eight.green) / (f -> norm);
//			image -> pixels[i][j].alpha = (temp.alpha + one.alpha + two.alpha + three.alpha + four.alpha + five.alpha + six.alpha + seven.alpha + eight.alpha) / (f -> norm);
//		}
//	}

//	return image;
	return NULL;
}

BoxFilter * readFilter(FILE * infile){
	
//	BoxFilter * box_filter = malloc(sizeof(BoxFilter));
//	char filter1[100];
//	char filter2[100];
//	char filter3[100];
//
//	fscanf(infile, "%s %s %s", filter1, filter2, filter3);
//	box_filter -> filter[0][0] = atof(filter1);
//	box_filter -> filter[0][1] = atof(filter2);
//	box_filter -> filter[0][2] = atof(filter3);
//	fscanf(infile, "%s %s %s", filter1, filter2, filter3);
//	box_filter -> filter[1][0] = atof(filter1);
//	box_filter -> filter[1][1] = atof(filter2);
//	box_filter -> filter[1][2] = atof(filter3);
//	fscanf(infile, "%s %s %s", filter1, filter2, filter3);
//	box_filter -> filter[2][0] = atof(filter1);
//	box_filter -> filter[2][1] = atof(filter2);
//	box_filter -> filter[2][2] = atof(filter3);
//	fscanf(infile "%s", filter1);
//	box_filter -> norm = atof(filter1);
//
//
	return NULL;
}
// EXTRA CREDIT END
