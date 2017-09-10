#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "filterParallel.h"
#include "filter.h"

#define SINGLE_PIXEL_ABS_TOLERANCE 20
#define PIXELS_PERCENTAGE_ALLOWED 2

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage ./validate actual.bmp something.filter\n");
    return EXIT_FAILURE;
  }
  
  FILE * actualFile = fopen(argv[1], "r");
  FILE * expectedFile = fopen(argv[2], "r");
  FILE * open_filter = fopen(argv[3], "r");

  if (!actualFile || !expectedFile) {
    printf("Could not open both image files!\n");
  }


  BMPImage * actualImage = readImage(actualFile);
  BMPImage * expectedImage = readImage(expectedFile);
  BoxFilter filter = readFilter(open_filter);
  BMPImage * image2 = malloc(sizeof(BMPImage));
  image2 -> header = actualImage -> header;
  image2 -> norm_height = abs(actualImage -> header.height_px);
  image2 -> pixels = malloc(image2 -> norm_height * sizeof(Pixel *));
  for(int i = 0; i < image2 -> norm_height; i++)
  {
  	image2 -> pixels[i] = malloc(sizeof(Pixel) * image2 -> header.width_px);
  }
  apply(actualImage, image2, filter, 4);
  if (actualImage->norm_height != expectedImage->norm_height ||
      actualImage->header.width_px != expectedImage->header.width_px) {
    printf("Your image does not have the same dimensions as the expected image! Failed!\n");
    return EXIT_FAILURE;
  }

  uint64_t pixelsDifferent = 0;

  for (int row = 0; row < expectedImage->norm_height; row++) {
    for (int col = 0; col < expectedImage->header.width_px; col++) {
      unsigned int expectedPacked = * ((int *) &(expectedImage->pixels[row][col]));
      unsigned int actualPacked = * ((int *) &(actualImage->pixels[row][col]));
      for (int channel = 0; channel < 4; channel++) {
        int channelExpected = (expectedPacked & (0xFF << (8 * channel))) >> (8 * channel);
        int actualExpected = (actualPacked & (0xFF << (8 * channel))) >> (8 * channel);
        if (abs(channelExpected - actualExpected) > SINGLE_PIXEL_ABS_TOLERANCE) {
          pixelsDifferent++;
          break;
        }
      } 
    }
  }

  uint64_t totalPixels = (expectedImage->norm_height * expectedImage->header.width_px);
  double percentageDifference = (100.0 * pixelsDifferent) / (totalPixels);

  printf("%ld/%ld (%lf %%) pixels different. ", pixelsDifferent, totalPixels, percentageDifference);
  if (percentageDifference > PIXELS_PERCENTAGE_ALLOWED) {
    printf("Failed!\n");
    return EXIT_FAILURE;
  }

  printf("Passed!\n");
  return EXIT_SUCCESS;
}
