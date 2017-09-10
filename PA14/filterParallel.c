#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include "filterParallel.h"

void applyThread(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int tid, int numThreads) {
	Pixel temp, one, two, three, four, five, six, seven, eight;
	int red_pixel, blue_pixel, green_pixel, alpha_pixel;
	int length = ceil(imageIn -> norm_height / ((float) numThreads));

	int low = tid * length;
	int high = (tid + 1) * length;

	if(high > imageIn -> norm_height)
	{
		high = imageIn -> norm_height;
	}
	for(int i = low; i < high; i++)
	{
		if(i >= imageIn -> norm_height)
		{
			break;
		}
		for(int j = 0; j < imageIn -> header.width_px; j++)
		{
			one = currentPixel(imageIn, i - 1, j - 1);
			two = currentPixel(imageIn, i - 1, j);
			three = currentPixel(imageIn, i - 1, j + 1);
			four = currentPixel(imageIn, i, j - 1);
			temp = currentPixel(imageIn, i, j);
			five = currentPixel(imageIn, i, j + 1);
			six = currentPixel(imageIn, i + 1, j - 1);
			seven = currentPixel(imageIn, i + 1, j);
			eight = currentPixel(imageIn, i + 1, j + 1);

			red_pixel = (one.red * f.filter[0][0] + two.red * f.filter[0][1] + three.red * f.filter[0][2] + four.red * f.filter[1][0] + temp.red * f.filter[1][1] + five.red * f.filter[1][2] + six.red * f.filter[2][0] + seven.red * f.filter[2][1] + eight.red * f.filter[2][2]);
			red_pixel = red_pixel / f.norm;
			if(red_pixel > 255)
			{
				red_pixel = 255;
			}
			if(red_pixel < 0)
			{
				red_pixel = 0;
			}
			imageOut -> pixels[i][j].red = (uint8_t) red_pixel;	
			
			blue_pixel = (one.blue * f.filter[0][0] + two.blue * f.filter[0][1] + three.blue * f.filter[0][2] + four.blue * f.filter[1][0] + temp.blue * f.filter[1][1] + five.blue * f.filter[1][2] + six.blue * f.filter[2][0] + seven.blue * f.filter[2][1] + eight.blue * f.filter[2][2]);
			blue_pixel = blue_pixel / f.norm;
			if(blue_pixel > 255)
			{
				blue_pixel = 255;
			}
			if(blue_pixel < 0)
			{
				blue_pixel = 0;
			}
			imageOut -> pixels[i][j].blue = (uint8_t) blue_pixel;
			
			green_pixel = (one.green * f.filter[0][0] + two.green * f.filter[0][1] + three.green * f.filter[0][2] + four.green * f.filter[1][0] + temp.green * f.filter[1][1] + five.green * f.filter[1][2] + six.green * f.filter[2][0] + seven.green * f.filter[2][1] + eight.green * f.filter[2][2]);
			green_pixel = green_pixel / f.norm;
			if(green_pixel > 255)
			{
				green_pixel = 255;
			}
			if(green_pixel < 0)
			{
				green_pixel = 0;
			}
			imageOut -> pixels[i][j].green = (uint8_t) green_pixel;


			alpha_pixel = (one.alpha * f.filter[0][0] + two.alpha * f.filter[0][1] + three.alpha * f.filter[0][2] + four.alpha * f.filter[1][0] + temp.alpha * f.filter[1][1] + five.alpha * f.filter[1][2] + six.alpha * f.filter[2][0] + seven.alpha * f.filter[2][1] + eight.alpha * f.filter[2][2]);
			alpha_pixel = alpha_pixel / f.norm;
			if(alpha_pixel > 255)
			{
				alpha_pixel = 255;
			}
			if(alpha_pixel < 0)
			{
				alpha_pixel = 0;
			}
			imageOut -> pixels[i][j].alpha = (uint8_t) alpha_pixel;
		}
	}
	//FILL IN. This is the work that thread #tid should do
	//You may find it useful to know the number of threads (numThreads) to
	//figure out what to do.
	
	return;
}

void * applyThreadWrapper(void * args) {
	ApplyArgs * applyArgs = (ApplyArgs *) args;
	fprintf(stdout, "calling thread %d\n", applyArgs->tid);
	
	applyThread(applyArgs->in, applyArgs->out, applyArgs->filter, applyArgs->tid, applyArgs->numThreads);
	
	fprintf(stdout, "finished with thread %d\n", applyArgs->tid);
	
	return NULL;
}

void apply(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int numThreads) {

	//FILL IN:
	//
	pthread_t * threads = malloc(sizeof(pthread_t) * numThreads);
	ApplyArgs * args = malloc(sizeof(ApplyArgs) * numThreads);

	for(int i = 0; i < numThreads; i++)
	{
		args[i].tid = i;
		args[i].numThreads = numThreads;
		args[i].in = imageIn;
		args[i].out = imageOut;
		args[i].filter = f;
	}

	for(int i = 0; i < numThreads; i++)
	{
		pthread_create(&threads[i], NULL, applyThreadWrapper, &args[i]);
	}

	for(int i = 0; i < numThreads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	free(args);
	free(threads);
	//1. create numThreads threads, that each call applyThreadWrapper
	//2. wait for all threads to finish
	//3. clean up any memory allocation you did.
	
}

Pixel currentPixel(BMPImage *  image, int i, int j)
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

//BoxFilter * readFilter(FILE * infile)
//{
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
	
//	return box_filter;
//}
