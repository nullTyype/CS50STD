#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *inputName = argv[1];

    // open file and opening validation;
    FILE *inputWav = fopen(inputName, "r");
    if (inputWav == NULL)
    {
        fclose(inputWav);
        printf("Invalid input file");
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    // reads and stores wavFile header info into header struct;
    fread(&header, sizeof(WAVHEADER), 1, inputWav);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);

    // Open output file for writing
    // TODO #5
    // output open and validation;
    char *outputName = argv[2];
    FILE *outputWav = fopen(argv[2], "w");
    if (outputWav == NULL)
    {
        fclose(outputWav);
        printf("Couldn't create %s\n", outputName);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outputWav);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    // buffer[0] is left channel while buffer[1] is the right channel;
    short **buffer = (short**)malloc(sizeof(short*) * header.numChannels);
    for (int i = 0; i < header.numChannels; i++)
    {
        buffer[i] = (short*)malloc(sizeof(short) * (header.subchunk2Size / blockSize));
    }
    // set offset to -4 bytes from begin
    fseek(inputWav, -4, SEEK_END);

    // reads inputWav data block, saving it to buffer array,
    // setting seek to 8 bytes from the last readed block to proper read;

    // read 2 times (from -8 bytes position) and saves it
    // in order to maintain the original sample channels configuration;
    // after that, sets pointer to -16 (the 8 already read and saved + the 8 new ones);

    do
    {
        fread(&buffer, blockSize, 1, inputWav);
        fwrite(&buffer, blockSize, 1, outputWav);
        fread(&buffer, blockSize, 1, inputWav);
        fwrite(&buffer, blockSize, 1, outputWav);
        fseek(inputWav, -16, SEEK_CUR);
        // printf("pointer pos: %li\n", ftell(inputWav));
    }
    while (ftell(inputWav) >= 44);

    fclose(inputWav);
    fclose(outputWav);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // wave format integer chars representation;
    int format[4] = {87, 65, 86, 69};

    // checks if header format matches WAVE files;
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != format[i])
        {
            return 1;
        }
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    // header has bits per sample but exercises asks por BYTES per sample;
    return (header.numChannels * (header.bitsPerSample/8));
}