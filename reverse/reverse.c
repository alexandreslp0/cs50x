#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
void revert_block(int block_size, char audio_block[block_size]);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse infile outfile\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER wh;
    fread(&wh, sizeof(WAVHEADER), 1, inptr);


    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(wh) == 1)
    {
        printf("Unsupported file format.\n");
    }

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&wh, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(wh);

    // Write reversed audio to file
    // TODO #8
    fseek(inptr, 0, SEEK_END);
    long int audio_size = ftell(inptr) - sizeof(WAVHEADER);
    long int number_of_blocks = audio_size / block_size;

    char *audio_block = malloc(block_size);
    fseek(inptr, ((-1) * block_size), SEEK_CUR);

    for (int i = 0; i < number_of_blocks; i++)
    {
        fseek(inptr, ((-2) * block_size), SEEK_CUR);
        fread(audio_block, block_size, 1, inptr);
        fwrite(audio_block, block_size, 1, outptr);

    }

    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' || header.format[1] == 'A' || header.format[2] == 'V' || header.format[3] == 'E')
    {
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}