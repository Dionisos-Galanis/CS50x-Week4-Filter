#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE meanC;
    double meanC1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            meanC1 = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            meanC = (BYTE) meanC1;
            image[i][j].rgbtBlue = meanC;
            image[i][j].rgbtGreen = meanC;
            image[i][j].rgbtRed = meanC;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE exchRGB;
    int half = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            exchRGB.rgbtBlue = image[i][j].rgbtBlue;
            exchRGB.rgbtGreen = image[i][j].rgbtGreen;
            exchRGB.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = exchRGB.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = exchRGB.rgbtGreen;
            image[i][width - j - 1].rgbtRed = exchRGB.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copying image
    RGBTRIPLE imageCP[height][width];
    // RGBTRIPLE black;
    // black.rgbtBlue = 0; black.rgbtGreen = 0; black.rgbtRed = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCP[i][j].rgbtBlue = image[i][j].rgbtBlue;
            imageCP[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCP[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }



    // Bluring image
    int sumBlue, sumGreen, sumRed;
    float nSum;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            nSum = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if ((i + k) >= 0 && (i + k) < height && (j + l) >= 0 && (j + l) < width)
                    {
                        sumBlue += imageCP[i + k][j + l].rgbtBlue;
                        sumGreen += imageCP[i + k][j + l].rgbtGreen;
                        sumRed += imageCP[i + k][j + l].rgbtRed;
                        nSum++;
                    }
                }
            }

            image[i][j].rgbtBlue = (BYTE) round(sumBlue / nSum);
            image[i][j].rgbtGreen = (BYTE) round(sumGreen / nSum);
            image[i][j].rgbtRed = (BYTE) round(sumRed / nSum);

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copying image
    // RGBTRIPLE imageCP[height + 2][width + 2];
    RGBTRIPLE* imageCP;
    imageCP = (RGBTRIPLE*) calloc((height + 2) * (width + 2), sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCP[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
            imageCP[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
            imageCP[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
        }
    }

    //Adding black borders
    // RGBTRIPLE black;
    // black.rgbtBlue = 0; black.rgbtGreen = 0; black.rgbtRed = 0;
    // for (int i = 0; i < height + 2; i++)
    // {
    //     imageCP[i][0].rgbtBlue = 0;
    //     imageCP[i][0].rgbtGreen = 0;
    //     imageCP[i][0].rgbtRed = 0;

    //     imageCP[i][width + 1].rgbtBlue = 0;
    //     imageCP[i][width + 1].rgbtGreen = 0;
    //     imageCP[i][width + 1].rgbtRed = 0;
    // }
    // for (int j = 0; j < width + 2; j++)
    // {
    //     imageCP[0][j].rgbtBlue = 0;
    //     imageCP[0][j].rgbtGreen = 0;
    //     imageCP[0][j].rgbtRed = 0;

    //     imageCP[height + 1][j].rgbtBlue = 0;
    //     imageCP[height + 1][j].rgbtGreen = 0;
    //     imageCP[height + 1][j].rgbtRed = 0;
    // }

    // // Copying image back for test
    // for (int i = 1; i < height + 1; i++)
    // {
    //     for (int j = 1; j < width + 1; j++)
    //     {
    //         image[i - 1][j - 1].rgbtBlue = imageCP[i][j].rgbtBlue;
    //         image[i - 1][j - 1].rgbtGreen = imageCP[i][j].rgbtGreen;
    //         image[i - 1][j - 1].rgbtRed = imageCP[i][j].rgbtRed;
    //     }
    // }

    BYTE sqrcut(int a, int b);
    int sumBlueX, sumGreenX, sumRedX;
    int sumBlueY, sumGreenY, sumRedY;
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            sumBlueX = 0;
            sumGreenX = 0;
            sumRedX = 0;
            sumBlueY = 0;
            sumGreenY = 0;
            sumRedY = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k == 0)
                    {
                        sumBlueX += l * 2 * imageCP[i + k][j + l].rgbtBlue;
                        sumGreenX += l * 2 * imageCP[i + k][j + l].rgbtGreen;
                        sumRedX += l * 2 * imageCP[i + k][j + l].rgbtRed;
                    }
                    else
                    {
                        sumBlueX += l * imageCP[i + k][j + l].rgbtBlue;
                        sumGreenX += l * imageCP[i + k][j + l].rgbtGreen;
                        sumRedX += l * imageCP[i + k][j + l].rgbtRed;
                    }

                    if (l == 0)
                    {
                        sumBlueY += k * 2 * imageCP[i + k][j + l].rgbtBlue;
                        sumGreenY += k * 2 * imageCP[i + k][j + l].rgbtGreen;
                        sumRedY += k * 2 * imageCP[i + k][j + l].rgbtRed;
                    }
                    else
                    {
                        sumBlueY += k * imageCP[i + k][j + l].rgbtBlue;
                        sumGreenY += k * imageCP[i + k][j + l].rgbtGreen;
                        sumRedY += k * imageCP[i + k][j + l].rgbtRed;
                    }
                }
            }

            // if (width < 5) // So it is a small file for debugging
            // {
            //     printf("GxR = %3d;  GxG = %3d; GxB = %3d\n", sumRedX, sumGreenX, sumBlueX);
            //     printf("GyR = %3d;  GyG = %3d; GyB = %3d\n\n", sumRedY, sumGreenY, sumBlueY);
            // }

            image[i - 1][j - 1].rgbtBlue = sqrcut(sumBlueX, sumBlueY);
            image[i - 1][j - 1].rgbtGreen = sqrcut(sumGreenX, sumGreenY);
            image[i - 1][j - 1].rgbtRed = sqrcut(sumRedX, sumRedY);

        }
    }


    return;
}

BYTE sqrcut(int a, int b)
{
    double sqrc = round(sqrt(pow(a, 2) + pow(b, 2)));
    if (sqrc > 255)
    {
        sqrc = 255;
    }
    return (BYTE) sqrc;
}