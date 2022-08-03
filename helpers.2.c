#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int G = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = G;
            image[i][j].rgbtGreen = G;
            image[i][j].rgbtBlue = G;
        }
    }
    return;
}

// Custom function to cap the sepia colors

unsigned char cap(int a)
{
    if (a > 255)
    {
        a = 255;
    }
    return a;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char x = image[i][j].rgbtRed;
            unsigned char y = image[i][j].rgbtGreen;
            unsigned char z = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = cap(round(x * 0.393 + y * 0.769 + z * 0.189));
            image[i][j].rgbtGreen = cap(round(x * 0.349 + y * 0.686 + z * 0.168));
            image[i][j].rgbtBlue = cap(round(x * 0.272 + y * 0.534 + z * 0.131));
        }
    }
    return;
}

//swap function
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int y = width % 2;
    int x = (width - y) / 2;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < x; j++)
        {
            swap(&image[i][j], &image[i][(width - 1) - j]);
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blr[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            blr[a][b].rgbtRed = image[a][b].rgbtRed;
            blr[a][b].rgbtGreen = image[a][b].rgbtGreen;
            blr[a][b].rgbtBlue = image[a][b].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0) //top left corner
            {
                image[i][j].rgbtRed = round((blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed + blr[i + 1][j].rgbtRed + blr[i + 1][j + 1].rgbtRed) / 4);
                image[i][j].rgbtGreen = round((blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen + blr[i + 1][j].rgbtGreen + blr[i + 1][j + 1].rgbtGreen) / 4);
                image[i][j].rgbtBlue = round((blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue + blr[i + 1][j].rgbtBlue + blr[i + 1][j + 1].rgbtBlue) / 4);
            }

            else if (i == 0 && j == (width - 1)) //top right corner
            {
                image[i][j].rgbtRed = round((blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed + blr[i + 1][j - 1].rgbtRed + blr[i + 1][j].rgbtRed) / 4);
                image[i][j].rgbtGreen = round((blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i + 1][j - 1].rgbtGreen + blr[i + 1][j].rgbtGreen) / 4);
                image[i][j].rgbtBlue = round((blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i + 1][j - 1].rgbtBlue + blr[i + 1][j].rgbtBlue) / 4);
            }

            else if (i == (height - 1) && j == 0) //bottom left corner
            {
                image[i][j].rgbtRed = round((blr[i - 1][j].rgbtRed + blr[i - 1][j + 1].rgbtRed + blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed) / 4);
                image[i][j].rgbtGreen = round((blr[i - 1][j].rgbtGreen + blr[i - 1][j + 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen) / 4);
                image[i][j].rgbtBlue = round((blr[i - 1][j].rgbtBlue + blr[i - 1][j + 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue) / 4);
            }

            else if (i == (height - 1) && j == (width - 1)) //bottom right corner
            {
                image[i][j].rgbtRed = round((blr[i - 1][j - 1].rgbtRed + blr[i - 1][j].rgbtRed + blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed) / 4);
                image[i][j].rgbtGreen = round((blr[i - 1][j - 1].rgbtGreen + blr[i - 1][j].rgbtGreen + blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen) / 4);
                image[i][j].rgbtBlue = round((blr[i - 1][j - 1].rgbtBlue + blr[i - 1][j].rgbtBlue + blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue) / 4);
            }

            else if (i > 0 && i < (height - 1) && j == 0) //left column
            {
                image[i][j].rgbtRed = round((blr[i - 1][j].rgbtRed + blr[i - 1][j + 1].rgbtRed + blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed + blr[i + 1][j].rgbtRed + blr[i + 1][j + 1].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((blr[i - 1][j].rgbtGreen + blr[i - 1][j + 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen + blr[i + 1][j].rgbtGreen + blr[i + 1][j + 1].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((blr[i - 1][j].rgbtBlue + blr[i - 1][j + 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue + blr[i + 1][j].rgbtBlue + blr[i + 1][j + 1].rgbtBlue) / 6);
            }

            else if (i > 0 && i < (height - 1) && j == (width - 1)) //right column
            {
                image[i][j].rgbtRed = round((blr[i - 1][j - 1].rgbtRed + blr[i - 1][j].rgbtRed + blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed + blr[i + 1][j - 1].rgbtRed + blr[i + 1][j].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((blr[i - 1][j - 1].rgbtGreen + blr[i - 1][j].rgbtGreen + blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i + 1][j - 1].rgbtGreen + blr[i + 1][j].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((blr[i - 1][j - 1].rgbtBlue + blr[i - 1][j].rgbtBlue + blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i + 1][j - 1].rgbtBlue + blr[i + 1][j].rgbtBlue) / 6);
            }

            else if (i == 0 && j > 0 && j < (width - 1)) //top row
            {
                image[i][j].rgbtRed = round((blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed + blr[i + 1][j - 1].rgbtRed + blr[i + 1][j].rgbtRed + blr[i + 1][j + 1].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen + blr[i + 1][j - 1].rgbtGreen + blr[i + 1][j].rgbtGreen + blr[i + 1][j + 1].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue + blr[i + 1][j - 1].rgbtBlue + blr[i + 1][j].rgbtBlue + blr[i + 1][j + 1].rgbtBlue) / 6);
            }

            else if (i == (height - 1) && j > 0 && j < (width - 1)) //bottom row
            {
                image[i][j].rgbtRed = round((blr[i - 1][j - 1].rgbtRed + blr[i - 1][j].rgbtRed + blr[i - 1][j + 1].rgbtRed + blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((blr[i - 1][j - 1].rgbtGreen + blr[i - 1][j].rgbtGreen + blr[i - 1][j + 1].rgbtGreen + blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((blr[i - 1][j - 1].rgbtBlue + blr[i - 1][j].rgbtBlue + blr[i - 1][j + 1].rgbtBlue + blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue) / 6);
            }

            else //middle pixels
            {
                image[i][j].rgbtRed = round((blr[i - 1][j - 1].rgbtRed + blr[i - 1][j].rgbtRed + blr[i - 1][j + 1].rgbtRed + blr[i][j - 1].rgbtRed + blr[i][j].rgbtRed + blr[i][j + 1].rgbtRed + blr[i + 1][j - 1].rgbtRed + blr[i + 1][j].rgbtRed + blr[i + 1][j + 1].rgbtRed) / 9);
                image[i][j].rgbtGreen = round((blr[i - 1][j - 1].rgbtGreen + blr[i - 1][j].rgbtGreen + blr[i - 1][j + 1].rgbtGreen + blr[i][j - 1].rgbtGreen + blr[i][j].rgbtGreen + blr[i][j + 1].rgbtGreen + blr[i + 1][j - 1].rgbtGreen + blr[i + 1][j].rgbtGreen + blr[i + 1][j + 1].rgbtGreen) / 9);
                image[i][j].rgbtBlue = round((blr[i - 1][j - 1].rgbtBlue + blr[i - 1][j].rgbtBlue + blr[i - 1][j + 1].rgbtBlue + blr[i][j - 1].rgbtBlue + blr[i][j].rgbtBlue + blr[i][j + 1].rgbtBlue + blr[i + 1][j - 1].rgbtBlue + blr[i + 1][j].rgbtBlue + blr[i + 1][j + 1].rgbtBlue) / 9);
            }
        }
    }
    return;
}