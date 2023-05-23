#include "helpers.h"
#include <stdio.h>
#include <math.h>

int capValue(int value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // average value of each pixel rgb values to determine grayscaled pixel intensity;
            // has to be cast-typed to float avoiding bugs;
            int average = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // width/2 means each left part pixels is going to swap
        // with right side pixels (it's counterpart),
        // otherwise the swap wouldn't make any effect
        // since swap would undo itself;
        for (int j = 0, roundedW = round(width/2); j < roundedW; j++)
        {
            // set holder before swap values;
            RGBTRIPLE holder = image[i][j];
            // swaps pixel from base pixel with it's counter-part;
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = holder;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            // corner validations;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        sumR += image[k][l].rgbtRed;
                        sumG += image[k][l].rgbtGreen;
                        sumB += image[k][l].rgbtBlue;
                        count++;
                    }
                }
            }
            imageCpy[i][j].rgbtRed = round(((float)sumR / count));
            imageCpy[i][j].rgbtGreen = round(((float)sumG / count));
            imageCpy[i][j].rgbtBlue = round(((float)sumB / count));
        }
    }

    // assign one value from another to original image array;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCpy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];

    // loop looks at each pixel and check if it's valid;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // arr[0] means to X while arr[1] means to Y;
            int sumR[2] = {0,0}, sumG[2] = {0,0}, sumB[2] = {0,0};
            // counter that fetchs Gx and Gy pos;
            int count = 0;
            // kernels def
            int Gx[9] = {-1,0,1,
                         -2,0,2,
                         -1,0,1};

            int Gy[9] = {-1,-2,-1,
                          0,0,0,
                          1,2,1};

            // validation to avoid seg fault errors;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l < width && l >= 0)
                    {
                        // Gx kernel operations;
                        // takes sum[0] that stores values for X sums,
                        // multiplying each value by it's kernel value;
                        sumR[0] += image[k][l].rgbtRed * (Gx[count]);
                        sumG[0] += image[k][l].rgbtGreen * (Gx[count]);
                        sumB[0] += image[k][l].rgbtBlue * (Gx[count]);
                        // Gy kernel operations;
                        // takes sum[1] that stores values for Y sums,
                        // multiplying each value by it's kernel value;
                        sumR[1] += image[k][l].rgbtRed * (Gy[count]);
                        sumG[1] += image[k][l].rgbtGreen * (Gy[count]);
                        sumB[1] += image[k][l].rgbtBlue * (Gy[count]);
                    }
                    count++;
                }
            }
            // rounds after calculates Gx^2 + Gy^2;
            // cap values at maximum of 255;

            imageCpy[i][j].rgbtRed = capValue(round(sqrt(pow(sumR[0], 2) + pow(sumR[1], 2))));
            imageCpy[i][j].rgbtGreen = capValue(round(sqrt(pow(sumG[0], 2) + pow(sumG[1], 2))));
            imageCpy[i][j].rgbtBlue = capValue(round(sqrt(pow(sumB[0], 2) + pow(sumB[1], 2))));
        }
    }

    // set imageCpy to image properly,
    // can't set image in main loop because changed values
    // changes next pixel's result;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCpy[i][j];
        }
    }
    return;
}

int capValue(int value)
{
    if (value > 255)
    {
        return 255;
    }

    return value;
}