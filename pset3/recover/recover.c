#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512 //BYTES
#define FILENAME_LEN 8

int main(int argc, char *argv[])
{
    // ensure proper usage.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover cardname\n");
        return 1;
    }

    // open memory card file.
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open.\n");
        return 2;
    }

    // array to store filenames.
    char filename[FILENAME_LEN];

    // array to readinto blocks of memory.
    unsigned char buffer[BUFFER_SIZE];

    // to keep track of number of images recovered.
    int numOfImgs = 0;

    // pointer to outfile
    FILE *outptr = NULL;

    // reading 512byte memory block into buffer
    while (fread(buffer, 1, BUFFER_SIZE, inptr) == BUFFER_SIZE)
    {
        // checking whether we found a starting of a new jpeg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] && buffer[2] == 0xff
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // then closing the previously created file.
            if (numOfImgs > 0)
            {
                fclose(outptr);
            }

            // giving a name to newly found jpeg file.
            sprintf(filename, "%03i.jpg", numOfImgs);

            // open newly created jpeg for further writting.
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not open image file\n");
                return 3;

            }

            // thus, we found a new jpeg so incrementing the numOfImgs
            numOfImgs++;
        }

        // writing the memory block to outfile till any outfile exist.
        if (outptr != NULL)
        {
            fwrite(buffer, 1, BUFFER_SIZE, outptr);
        }
    }// if we are out of this while loop that will mean that we've arrived at the EOF, because last block of the card will always be slightly shorter in memory than the BUFFER_SIZE i.e., 512 bytes

    // closing last created jpeg.
    fclose(outptr);

    // closing the memory-card.
    fclose(inptr);

    // success
    return 0;
}
