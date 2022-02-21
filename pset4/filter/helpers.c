#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = roundf((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) * .333333);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
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
            RGBTRIPLE tmp;
            if ((.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue) > 255)
            {
                tmp.rgbtBlue = 255;
            }
            else
            {
                tmp.rgbtBlue = roundf(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            }
            if ((.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue) > 255)
            {
                tmp.rgbtRed = 255;
            }
            else
            {
                tmp.rgbtRed = roundf(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            }
            if ((.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue) > 255)
            {
                tmp.rgbtGreen = 255;
            }
            else
            {
                tmp.rgbtGreen = roundf(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            }
            image[i][j].rgbtBlue = tmp.rgbtBlue;
            image[i][j].rgbtRed = tmp.rgbtRed;
            image[i][j].rgbtGreen = tmp.rgbtGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    int middle = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < middle; j++)
        {
            //Store pixel to be swapped in tmp
            tmp.rgbtRed = image[i][width - (j + 1)].rgbtRed;
            tmp.rgbtBlue = image[i][width - (j + 1)].rgbtBlue;
            tmp.rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            //change (width - i)'th pixel to i'th pixel
            image[i][width - (j + 1)].rgbtRed = image[i][j].rgbtRed;
            image[i][width - (j + 1)].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - (j + 1)].rgbtGreen = image[i][j].rgbtGreen;
            //change i'th pixel to (width - i)'th pixel
            image[i][j].rgbtRed = tmp.rgbtRed;
            image[i][j].rgbtBlue = tmp.rgbtBlue;
            image[i][j].rgbtGreen = tmp.rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float sumRed;
    float sumBlue;
    float sumGreen;
    float counter;
    RGBTRIPLE oimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oimage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Reset sum & counter
            sumRed = oimage[i][j].rgbtRed;
            sumBlue = oimage[i][j].rgbtBlue;
            sumGreen = oimage[i][j].rgbtGreen;
            counter = 1.0;
            //check which surrounding pixels exist
            if (i != 0)
            {
                sumRed += oimage[i - 1][j].rgbtRed;
                sumBlue += oimage[i - 1][j].rgbtBlue;
                sumGreen += oimage[i - 1][j].rgbtGreen;
                counter += 1;
            }
            if (i < (height - 1))
            {
                sumRed += oimage[i + 1][j].rgbtRed;
                sumBlue += oimage[i + 1][j].rgbtBlue;
                sumGreen += oimage[i + 1][j].rgbtGreen;
                counter += 1;
            }
            if (j != 0)
            {
                sumRed += oimage[i][j - 1].rgbtRed;
                sumBlue += oimage[i][j - 1].rgbtBlue;
                sumGreen += oimage[i][j - 1].rgbtGreen;
                counter += 1;
            }
            if (j < (width - 1))
            {
                sumRed += oimage[i][j + 1].rgbtRed;
                sumBlue += oimage[i][j + 1].rgbtBlue;
                sumGreen += oimage[i][j + 1].rgbtGreen;
                counter += 1;
            }
            if (i != 0 && j != 0)
            {
                sumRed += oimage[i - 1][j - 1].rgbtRed;
                sumBlue += oimage[i - 1][j - 1].rgbtBlue;
                sumGreen += oimage[i - 1][j - 1].rgbtGreen;
                counter += 1;
            }
            if (i != 0 && j < (width - 1))
            {
                sumRed += oimage[i - 1][j + 1].rgbtRed;
                sumBlue += oimage[i - 1][j + 1].rgbtBlue;
                sumGreen += oimage[i - 1][j + 1].rgbtGreen;
                counter += 1;
            }
            if (i < (height - 1) && j < (width - 1))
            {
                sumRed += oimage[i + 1][j + 1].rgbtRed;
                sumBlue += oimage[i + 1][j + 1].rgbtBlue;
                sumGreen += oimage[i + 1][j + 1].rgbtGreen;
                counter += 1;
            }
            if (i < (height - 1) && j != 0)
            {
                sumRed += oimage[i + 1][j - 1].rgbtRed;
                sumBlue += oimage[i + 1][j - 1].rgbtBlue;
                sumGreen += oimage[i + 1][j - 1].rgbtGreen;
                counter += 1;
            }
            counter = counter / 1.0;
            //Calculate and replace rgb values with average
            image[i][j].rgbtRed = roundf(sumRed / (counter * 1.0));
            image[i][j].rgbtBlue = roundf(sumBlue / (counter * 1.0));
            image[i][j].rgbtGreen = roundf(sumGreen / (counter * 1.0));

        }
    }
    return;
}
