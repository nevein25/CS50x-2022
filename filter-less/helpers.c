#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int rounded = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rounded;
            image[i][j].rgbtGreen = rounded;
            image[i][j].rgbtRed = rounded;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            // Computing new red, green, and blue values for sepia effect
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int r = 0; r < height; r++)
    {
        for (int c = width - 1, n = 0; c >= 0; c--, n++)
        {
            image[r][n] =  temp[r][c] ;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image so no rewrite happend during the blur
    RGBTRIPLE temp[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width ; c++)
        {
            temp[r][c] = image[r][c];
        }
    }

    // Looping in the whole original image
    //The main loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {

            int theRed = 0;
            int theGreen = 0;
            int theBlue = 0;

            // Blur every pixel by avg 3 x 3 arround each pixel, except for corner and edges
            int counter = 0;
            for (int r = i - 1, n = 0 ; n < 3; r++, n++)
            {
                for (int c = j - 1, n2 = 0; n2 < 3 ; c++, n2++)
                {
                    if (r < 0 || r >= height || c < 0 || c >= width)
                    {
                        continue;
                    }
                    theRed = theRed + temp[r][c].rgbtRed;
                    theGreen = theGreen + temp[r][c].rgbtGreen;
                    theBlue = theBlue + temp[r][c].rgbtBlue;
                    counter++;
                }
            }
            // Avg the value for red, blue and green
            int blurRed = round(theRed / (float) counter);
            int blurBlue  = round(theBlue / (float)  counter);
            int blurGreen  = round(theGreen / (float)  counter);

            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtBlue = blurBlue;
            image[i][j].rgbtGreen = blurGreen;

        }
    }

    return;
}
