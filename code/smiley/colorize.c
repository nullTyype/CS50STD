#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "helpers.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: colorize infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // read infile's BITMAPFILEHEADER
    // set bitmap file header as custom struc created at bmp.h;
    // read file information (size, type and layout) from input file saving it in bf(bitmapFile) var;
    // file header contains information about size, type and the layout from the bmp file;
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    // read contents from file and stores it in bi(bitmapInfo) var;
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // set height and width data extracted from input bitmap;
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // allocate memory for image
    // names *image pointer of image width size of bytes to represents image rgb data, a 24 bits(3 bytes) data format to represents colors;
    // calloc allocates (height times) the amount of bytes of (width * RGBTRIPLE), creating a struc with height amount of elements,
    // each with width * RGBTRIPLE size of bytes;
    RGBTRIPLE (*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // determine padding for scanlines
    // set padding of lines;
    int padding =  (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    // set correctly spaces between lines, using fseek to jump padding spaces after read image row;
    for (int i = 0; i < height; i++)
    {
        // read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // search over height and width grid checking for black pixels;
    colorize(height, width, image);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // free memory for image
    free(image);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;
}
