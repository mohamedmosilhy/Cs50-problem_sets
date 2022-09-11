#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            float avg = (r + g + b) / 3.0;
            avg = round(avg);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            float sepiaRed = .393 * r + .769 * g + .189 * b;
            float sepiaGreen = .349 * r + .686 * g + .168 * b;
            float sepiaBlue = .272 * r + .534 * g + .131 * b;
            sepiaRed = round(sepiaRed);
            if (sepiaRed > 255)
            {
                sepiaRed = 255 ;
            }
            sepiaGreen = round(sepiaGreen);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255 ;
            }
            sepiaBlue = round(sepiaBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255 ;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if ((width % 2) == 0)
        {
            int a = width / 2;
            int b = width - 1 ;
            for (int j = 0; j < a; j++)
            {
                RGBTRIPLE new_pixel;
                new_pixel = image[i][j];
                image[i][j] = image[i][b];
                image[i][b] = new_pixel;
                b--;
            }
        }
        else
        {
            int a = (width - 1) / 2;
            int b = width - 1 ;
            for (int j = 0; j < a; j++)
            {
                RGBTRIPLE new_pixel;
                new_pixel = image[i][j];
                image[i][j] = image[i][b];
                image[i][b] = new_pixel;
                b--;

            }
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imgCopy[height][width];
    float avg_red;
    float avg_blue;
    float avg_green;
    //create a copy of original image to save original pixel values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imgCopy[i][j].rgbtRed = image[i][j].rgbtRed;
	        imgCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
	        imgCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //if the pixel is on the top left edge
            if ((i == 0) && (j == 0))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i][j + 1].rgbtRed + imgCopy[i + 1][j].rgbtRed + imgCopy[i + 1][j + 1].rgbtRed) / 4.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue + imgCopy[i + 1][j].rgbtBlue + imgCopy[i + 1][j + 1].rgbtBlue) /
                           4.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen + imgCopy[i + 1][j].rgbtGreen + imgCopy[i + 1][j +
                             1].rgbtGreen) / 4.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on top Right
            else if ((i == 0) && (j == (width - 1)))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j - 1].rgbtRed + imgCopy[i][j].rgbtRed + imgCopy[i + 1][j - 1].rgbtRed + imgCopy[i + 1][j].rgbtRed) / 4.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j - 1].rgbtBlue + imgCopy[i][j].rgbtBlue + imgCopy[i + 1][j - 1].rgbtBlue + imgCopy[i + 1][j].rgbtBlue) /
                           4.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j - 1].rgbtGreen + imgCopy[i][j].rgbtGreen + imgCopy[i + 1][j - 1].rgbtGreen + imgCopy[i +
                             1][j].rgbtGreen) / 4.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on the lower left edge
            else if ((i == (height - 1)) && (j == 0))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i][j + 1].rgbtRed + imgCopy[i - 1][j].rgbtRed + imgCopy[i - 1][j + 1].rgbtRed) / 4.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue + imgCopy[i - 1][j].rgbtBlue + imgCopy[i - 1][j + 1].rgbtBlue) /
                           4.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen + imgCopy[i - 1][j].rgbtGreen + imgCopy[i - 1][j +
                             1].rgbtGreen) / 4.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on lower right
            else if (i == (height - 1) && j == (width - 1))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i - 1][j - 1].rgbtRed + imgCopy[i - 1][j].rgbtRed + imgCopy[i][j - 1].rgbtRed + imgCopy[i][j].rgbtRed) / 4.0;
                // claculate the avg of blue colour
		 		avg_blue = (imgCopy[i - 1][j - 1].rgbtBlue + imgCopy[i - 1][j].rgbtBlue + imgCopy[i][j - 1].rgbtBlue + imgCopy[i][j].rgbtBlue) /
                           4.0;
                // claculate the avg of green colour
				avg_green = (imgCopy[i - 1][j - 1].rgbtGreen + imgCopy[i - 1][j].rgbtGreen + imgCopy[i][j - 1].rgbtGreen +
                             imgCopy[i][j].rgbtGreen) / 4.0;

				avg_red = round(avg_red);
				avg_green = round(avg_green);
				avg_blue = round(avg_blue);

				image[i][j].rgbtRed = avg_red;
				image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtBlue = avg_blue;
            }
            //if the pixel is on left side
            else if ((j == 0) && ((i > 0) && (i < (height - 1))))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i - 1][j].rgbtRed + imgCopy[i + 1][j].rgbtRed + imgCopy[i][j + 1].rgbtRed +
                           imgCopy[i - 1][j + 1].rgbtRed + imgCopy[i + 1][j + 1].rgbtRed) / 6.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i - 1][j].rgbtBlue + imgCopy[i + 1][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue +
                            imgCopy[i - 1][j + 1].rgbtBlue + imgCopy[i + 1][j + 1].rgbtBlue) / 6.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i - 1][j].rgbtGreen + imgCopy[i + 1][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen +
                             imgCopy[i - 1][j + 1].rgbtGreen + imgCopy[i + 1][j + 1].rgbtGreen) / 6.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on right side
            else if ((j == (width - 1)) && ((i > 0) && (i < (height - 1))))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i + 1][j].rgbtRed + imgCopy[i - 1][j].rgbtRed + imgCopy[i][j - 1].rgbtRed +
                           imgCopy[i - 1][j - 1].rgbtRed + imgCopy[i + 1][j - 1].rgbtRed) / 6.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i + 1][j].rgbtBlue + imgCopy[i - 1][j].rgbtBlue + imgCopy[i][j - 1].rgbtBlue +
                            imgCopy[i - 1][j - 1].rgbtBlue + imgCopy[i + 1][j - 1].rgbtBlue) / 6.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i + 1][j].rgbtGreen + imgCopy[i - 1][j].rgbtGreen + imgCopy[i][j - 1].rgbtGreen +
                             imgCopy[i - 1][j - 1].rgbtGreen + imgCopy[i + 1][j - 1].rgbtGreen) / 6.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on upper side
            else if ((i == 0) && ((j > 0) && (j < (width - 1))))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i][j + 1].rgbtRed + imgCopy[i][j - 1].rgbtRed + imgCopy[i + 1][j].rgbtRed +
                           imgCopy[i + 1][j - 1].rgbtRed + imgCopy[i + 1][j + 1].rgbtRed) / 6.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue + imgCopy[i][j - 1].rgbtBlue + imgCopy[i + 1][j].rgbtBlue +
                            imgCopy[i + 1][j - 1].rgbtBlue + imgCopy[i + 1][j + 1].rgbtBlue) / 6.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen + imgCopy[i][j - 1].rgbtGreen + imgCopy[i + 1][j].rgbtGreen +
                             imgCopy[i + 1][j - 1].rgbtGreen + imgCopy[i + 1][j + 1].rgbtGreen) / 6.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on lower side
            else if ((i == (height - 1)) && ((j > 0) && (j < (width - 1))))
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i][j + 1].rgbtRed + imgCopy[i][j - 1].rgbtRed + imgCopy[i - 1][j].rgbtRed +
                           imgCopy[i - 1][j - 1].rgbtRed + imgCopy[i - 1][j + 1].rgbtRed) / 6.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue + imgCopy[i][j - 1].rgbtBlue + imgCopy[i - 1][j].rgbtBlue +
                            imgCopy[i - 1][j - 1].rgbtBlue + imgCopy[i - 1][j + 1].rgbtBlue) / 6.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen + imgCopy[i][j - 1].rgbtGreen + imgCopy[i - 1][j].rgbtGreen +
                             imgCopy[i - 1][j - 1].rgbtGreen + imgCopy[i - 1][j + 1].rgbtGreen) / 6.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
            //if the pixel is on the middle and can form a 3x3 grid
            else
            {
                // claculate the avg of red colour
                avg_red = (imgCopy[i][j].rgbtRed + imgCopy[i][j + 1].rgbtRed + imgCopy[i][j - 1].rgbtRed + imgCopy[i - 1][j].rgbtRed +
                           imgCopy[i - 1][j - 1].rgbtRed + imgCopy[i - 1][j + 1].rgbtRed + imgCopy[i + 1][j].rgbtRed + imgCopy[i + 1][j + 1].rgbtRed +
                           imgCopy[i + 1][j - 1].rgbtRed) / 9.0;
                // claculate the avg of blue colour
                avg_blue = (imgCopy[i][j].rgbtBlue + imgCopy[i][j + 1].rgbtBlue + imgCopy[i][j - 1].rgbtBlue + imgCopy[i - 1][j].rgbtBlue +
                            imgCopy[i - 1][j - 1].rgbtBlue + imgCopy[i - 1][j + 1].rgbtBlue + imgCopy[i + 1][j].rgbtBlue +
                            imgCopy[i + 1][j + 1].rgbtBlue + imgCopy[i + 1][j - 1].rgbtBlue) / 9.0;
                // claculate the avg of green colour
                avg_green = (imgCopy[i][j].rgbtGreen + imgCopy[i][j + 1].rgbtGreen + imgCopy[i][j - 1].rgbtGreen + imgCopy[i - 1][j].rgbtGreen +
                             imgCopy[i - 1][j - 1].rgbtGreen + imgCopy[i - 1][j + 1].rgbtGreen + imgCopy[i + 1][j].rgbtGreen +
                             imgCopy[i + 1][j + 1].rgbtGreen + imgCopy[i + 1][j - 1].rgbtGreen) / 9.0;


                avg_red = round(avg_red);
                avg_blue = round(avg_blue);
                avg_green = round(avg_green);

                image[i][j].rgbtBlue = avg_blue;
                image[i][j].rgbtGreen = avg_green;
                image[i][j].rgbtRed = avg_red;
            }
        }
    }

    return;
}
