// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize N infile outfile\n");
        return 1;
    }

    // converting resizing factor to an integer type.
    int n = atoi(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // makaing resizing changes by a factor of n to the BITMAPFILEHADER
    int width = bi.biWidth, height = bi.biHeight;  // storing old values of biWidth and biheight to iterate over pixels in future.
    int ResizedWidth = width * n, ResizedHeight = height * n;

    // making associaated changes with resizing in headers of bitmapfile.
    bi.biHeight = ResizedHeight;
    bi.biWidth = ResizedWidth;
    int inFilePadding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;  // padding for infile's scanline
    int outFilePadding = (4 - (ResizedWidth * sizeof(RGBTRIPLE)) % 4) % 4;  //padding for outfile's scanline
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * ResizedWidth) + outFilePadding) * abs(ResizedHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // creating an array of type RGBTRIPLE to store one scanline.
    RGBTRIPLE PixelRow[ResizedWidth * sizeof(RGBTRIPLE)]; // i.e., we will be storing scanlines without padding.

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // storing a scanline in temporary array
            for (int k = 0; k < n; k++)
            {
                PixelRow[(j * n) + k] = triple;

            }
        }

        // skip over padding, if any
        fseek(inptr, inFilePadding, SEEK_CUR);

        // writing scanline form PixelRow array n times
        for (int j = 0; j < n; j++)
        {
            // write  scanline stored at PixelRow
            fwrite(PixelRow, sizeof(RGBTRIPLE), ResizedWidth, outptr);

            // write new paadding
            for (int k = 0; k < outFilePadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
