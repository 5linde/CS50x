#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover input.raw\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // create buffer to store data in
    uint8_t buffer[512];

    // Allocate enough space for new filenames ###.jpg = 7 + 1 for "\0"
    char filename[8];

    // Declaring output file as NULL to avoid error of undeclared variable
    // when closing the file
    FILE *output = NULL;

    // Keep track of how many JPEGs have been found (used in new img filename)
    int counter = 0;

    bool jpegFound = false;

    while (fread(buffer, 1, sizeof(buffer), input) == sizeof(buffer))
    {
        // Check if first 4 bytes of buffer is the start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "w");
            }
            else
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "w");
            }

            jpegFound = true;
            counter++;
        }

        // Continue to write to output file until new JPEG is found
        if (jpegFound)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }
    }

    // Close all files and free all allocated memory
    fclose(input);
    fclose(output);
}
