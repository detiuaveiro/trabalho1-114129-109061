// imageTest - A program that performs some image processing.
//
// This program is an example use of the image8bit module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// João Manuel Rodrigues <jmr@ua.pt>
// 2023

#include <assert.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image8bit.h"
#include "instrumentation.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    error(1, 0, "Usage: imageTest input.pgm output.pgm");
  }

  ImageInit();

  printf("# LOAD image");
  InstrReset(); // to reset instrumentation
  Image img1 = ImageLoad(argv[1]);
  if (img1 == NULL)
  {
    error(2, errno, "Loading %s: %s", argv[1], ImageErrMsg());
  }
  InstrPrint(); // to print instrumentation

  // Try changing the behaviour of the program by commenting/uncommenting
  // the appropriate lines.

  // img2 = ImageCrop(img1, ImageWidth(img1)/4, ImageHeight(img1)/4, ImageWidth(img1)/2, ImageHeight(img1)/2);
  // Image img2 = ImageCrop(img1, 5, 78, ImageWidth(img1) / 2, ImageHeight(img1) / 3);

  // test ImageLocateSubImage(Image img1, int *px, int *py, Image img2)

  int px, py;
  // ImageLocateSubImage(img1, &px, &py, img2);
  // printf("px = %d, py = %d\n", px, py);

  // if (img2 == NULL)
  // {
  //   error(2, errno, "Rotating img2: %s", ImageErrMsg());
  // }

  // Image img2 = ImageLoad(argv[1]);

  // Test ImageCrop(Image img, int x, int y, int w, int h)
  // criar pgm 1 pixel:
  Image img2 = ImageCreate(1, 1, 255);
  // defini-lo todo preto:
  ImageSetPixel(img2, 0, 0, 0);

  Image img3 = ImageCreate(640, 480, 255);
  // definir tudo branco
  for (int i = 0; i < 640; i++)
    for (int j = 0; j < 480; j++)
      ImageSetPixel(img3, i, j, 255);

  // testar a ImageLocateSubImage com img1 e img2 (worst case)

  // InstrReset();
  // ImageLocateSubImage(img3, &px, &py, img2);
  // InstrPrint();

  printf("px = %d, py = %d\n", px, py);

  // Test ImageBlur(Image img, int dx, int dy)
  // ImageBlur(img2, 3, 3);
  // mais blur
  InstrReset();
  ImageBlur(img2, 3, 3);
  InstrPrint();
  // ainda mais blured
  // InstrReset();
  // ImageBlur(img2, 7, 7);
  // InstrPrint();
  // InstrReset();
  // ImageBlur(img2, 15, 15);
  // InstrPrint();

  // ImageNegative(img2);
  // ImageThreshold(img2, 100);
  // ImageBrighten(img2, 1.3);
  // ImageRotate(img2);

  if (ImageSave(img2, argv[2]) == 0)
  {
    error(2, errno, "%s: %s", argv[2], ImageErrMsg());
  }

  ImageDestroy(&img1);
  ImageDestroy(&img2);
  return 0;
}