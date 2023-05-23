#include <stdio.h>
#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // search over each image[i][j] and check if it's black
    // if true, changes all black pixels to a chosen color;

    // rgb sets colors to overwrite black pixels
    int RGB[3];
    // red;
    RGB[0] = 255;
    // green;
    RGB[1] = 87;
    // blue;
    RGB[2] = 51;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0 &&
                image[i][j].rgbtGreen == 0 &&
                image[i][j].rgbtBlue == 0)
            {
                image[i][j].rgbtRed = RGB[0];
                image[i][j].rgbtGreen = RGB[1];
                image[i][j].rgbtBlue = RGB[2];
            }
        }
    }

    return;
}
