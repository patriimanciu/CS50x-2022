#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //get the average of the RBG to turn it into gray
            gray = (image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0;
            image[j][i].rgbtBlue = image[j][i].rgbtGreen = image[j][i].rgbtRed = round(gray);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //use given formulas for the filter
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            //RGB doesn't support values over 255, therefore anything over that gets 255 as the value
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sepiaBlue);
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sepiaGreen);
            }
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;

            }
            else
            {
                image[i][j].rgbtRed = round(sepiaRed);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, new_width = width / 2; j < new_width; j++)
        {
            RGBTRIPLE temp;

            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy of image
    RGBTRIPLE copy_image[height][width];

    //handling everything but the corner and edge cases
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            float cnt = 0.00;

            //hacky adaptation to Lee's algorithm
            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    int currentI = i + k;
                    int currentJ = j + h;

                    if (currentI < 0 || currentJ < 0 || currentI > (height - 1) || currentJ > (width - 1))
                    {
                        continue;
                    }

                    sumR += image[currentI][currentJ].rgbtRed;
                    sumG += image[currentI][currentJ].rgbtGreen;
                    sumB += image[currentI][currentJ].rgbtBlue;
                    cnt++;
                }
            }
            copy_image[i][j].rgbtRed = round(sumR / cnt);
            copy_image[i][j].rgbtGreen = round(sumG / cnt);
            copy_image[i][j].rgbtBlue = round(sumB / cnt);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy_image[i][j].rgbtBlue;
        }
    }
    return;
}