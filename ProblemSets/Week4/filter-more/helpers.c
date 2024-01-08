#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float averageRGB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average RGB value
            averageRGB = round((float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            // Set old RGB values to the new average grayscale values
            image[i][j].rgbtRed = averageRGB;
            image[i][j].rgbtGreen = averageRGB;
            image[i][j].rgbtBlue = averageRGB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary pixel value holder
    RGBTRIPLE tempPixelHolder = {1, 1, 1};
    for (int i = 0; i < height; i++)
    {
        // Reflect pixels in every row by swapping 1st with last, 2nd with 2nd last etc.
        for (int j = 0; j < width / 2; j++)
        {
            tempPixelHolder = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tempPixelHolder;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    int totR, totG, totB, pixi_index, pixj_index, count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            totR = totG = totB = count = 0;

            // Find current pixels valid pixel neighbours in a 3x3 grid
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // Define pixel indexes for simplicity
                    pixi_index = i + x;
                    pixj_index = j + y;

                    // Check if neighbouring pixel is inside image boundaries and count nr of valid pixel neighbours for average
                    // division factor
                    if (pixi_index >= 0 && pixi_index <= (height - 1) && pixj_index >= 0 && pixj_index <= (width - 1))
                    {
                        // Calculate total color value sum of pixel neighbours
                        totR += image[pixi_index][pixj_index].rgbtRed;
                        totG += image[pixi_index][pixj_index].rgbtGreen;
                        totB += image[pixi_index][pixj_index].rgbtBlue;
                        count++;
                    }
                }
            }

            // Average RGB values and round to nearest int
            imageCopy[i][j].rgbtRed = round((float) totR / count);
            imageCopy[i][j].rgbtGreen = round((float) totG / count);
            imageCopy[i][j].rgbtBlue = round((float) totB / count);
        }
    }

    // Copy new values to image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCopy[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int rGx, rGy, gGx, gGy, bGx, bGy, newR, newG, newB, pixi_index, pixj_index;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rGx = rGy = gGx = gGy = bGx = bGy = 0;

            // Find current pixels valid pixel neighbours in a 3x3 grid
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    // Define pixel indexes for simplicity
                    pixi_index = i - 1 + x;
                    pixj_index = j - 1 + y;

                    // Check if neighbouring pixel is inside image boundaries
                    if (pixi_index >= 0 && pixi_index <= (height - 1) && pixj_index >= 0 && pixj_index <= (width - 1))
                    {
                        // Calculate Gx values for RGB
                        rGx += image[pixi_index][pixj_index].rgbtRed * Gx[x][y];
                        gGx += image[pixi_index][pixj_index].rgbtGreen * Gx[x][y];
                        bGx += image[pixi_index][pixj_index].rgbtBlue * Gx[x][y];

                        // Calculate Gy values for RGB
                        rGy += image[pixi_index][pixj_index].rgbtRed * Gy[x][y];
                        gGy += image[pixi_index][pixj_index].rgbtGreen * Gy[x][y];
                        bGy += image[pixi_index][pixj_index].rgbtBlue * Gy[x][y];
                    }
                }
            }

            // Calculate square root of Gx^2 + Gy^2 to obtain final value of the new pixel value
            newR = round(sqrt(pow(rGx, 2) + pow(rGy, 2)));
            newG = round(sqrt(pow(gGx, 2) + pow(gGy, 2)));
            newB = round(sqrt(pow(bGx, 2) + pow(bGy, 2)));

            if (newR > 255)
            {
                newR = 255;
            }

            if (newG > 255)
            {
                newG = 255;
            }

            if (newB > 255)
            {
                newB = 255;
            }

            imageCopy[i][j].rgbtRed = newR;
            imageCopy[i][j].rgbtGreen = newG;
            imageCopy[i][j].rgbtBlue = newB;
        }
    }

    // Copy new values to image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCopy[i][j];
        }
    }

    return;
}
