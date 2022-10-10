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
    // The main loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {

            int theRed = 0;
            int theGreen = 0;
            int theBlue = 0;

            // Blur every pixel by avg 3 x 3 arround each pixel
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image so no rewrite happen
    RGBTRIPLE temp[height][width];

    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width ; c++)
        {
            temp[r][c] = image[r][c];
        }
    }


    int Gx [][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy [][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Looping in the whole original image
    // The main loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {


            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;

            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            // Every pixel around the main cell (3 x 3) arround each pixel

            for (int r = i - 1, n = 0 ; n < 3; r++, n++)
            {
                for (int c = j - 1, n2 = 0; n2 < 3 ; c++, n2++)
                {
                    if (r < 0 || r >= height || c < 0 || c >= width)
                    {
                        // temp[r][c].rgbtRed = 0;
                        // temp[r][c].rgbtGreen = 0;
                        // temp[r][c].rgbtBlue = 0;
                        continue;
                    }

                    GxRed = Gx[n][n2] * temp[r][c].rgbtRed + GxRed;
                    GxGreen = Gx[n][n2] * temp[r][c].rgbtGreen + GxGreen;
                    GxBlue = Gx[n][n2] * temp[r][c].rgbtBlue + GxBlue;

                    GyRed = Gy[n][n2] * temp[r][c].rgbtRed + GyRed;
                    GyGreen = Gy[n][n2] * temp[r][c].rgbtGreen + GyGreen;
                    GyBlue = Gy[n][n2] * temp[r][c].rgbtBlue + GyBlue;
                }
            }
            int redEdge = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            int blueEdge = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
            int greenEdge = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

            if (blueEdge > 255)
            {
                blueEdge = 255;
            }
            if (redEdge > 255)
            {
                redEdge = 255;
            }
            if (greenEdge > 255)
            {
                greenEdge = 255;
            }
            image[i][j].rgbtRed = redEdge;
            image[i][j].rgbtBlue = blueEdge;
            image[i][j].rgbtGreen = greenEdge;

        }
    }


    return;
}
