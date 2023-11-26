void ImageBlur(Image img, int dx, int dy)
{
  int width = ImageWidth(img);
  int height = ImageHeight(img);
  int maxval = ImageMaxval(img);

  if (dx <= 0 || dy <= 0 || (dx % 2 == 0) || (dy % 2 == 0))
  {
    errno = EINVAL; // Invalid argument
    errCause = "Invalid filter size";
    return;
  }

  Image tempImg = ImageCreate(width, height, maxval);
  if (tempImg == NULL)
  {
    // Handle memory allocation failure
    return;
  }

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int sum = 0;
      int count = 0;

      for (int i = y - dy; i <= y + dy; i++)
      {
        for (int j = x - dx; j <= x + dx; j++)
        {
          if (ImageValidPos(img, j, i))
          {
            sum += ImageGetPixel(img, j, i);
            count++;
          }
        }
      }

      double mean = (double)sum / count;
      uint8_t roundedValue = (uint8_t)(mean + 0.5);

      ImageSetPixel(tempImg, x, y, roundedValue);
    }
  }

  // Copy the temporary image back to the original image
  for (int i = 0; i < width * height; i++)
  {
    img->pixel[i] = tempImg->pixel[i];
  }

  ImageDestroy(&tempImg);
}