// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Allocate 44 bytes of memory for wav header
    uint8_t *headerCopy = malloc(sizeof(uint8_t) * HEADER_SIZE);

    // Copy header from input to output file
    fread(headerCopy, HEADER_SIZE, 1, input);
    fwrite(headerCopy, HEADER_SIZE, 1, output);

    free(headerCopy);

    // TODO: Read samples from input file and write updated data to output file
    // Allocate 2 bytes of memory for samples
    int16_t *buffer = malloc(sizeof(int16_t));

    // While !EOL copy samples from input to output file and modify sample with specified factor
    while (fread(buffer, sizeof(int16_t), 1, input) == 1)
    {
        *buffer *= factor;
        fwrite(buffer, sizeof(int16_t), 1, output);
    }

    free(buffer);

    // Close files
    fclose(input);
    fclose(output);
}
