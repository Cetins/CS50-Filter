#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find the average value of colors in the pixel then round it
            int G = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            //set the same value to each color to stay in the gray scale
            image[i][j].rgbtRed = G;
            image[i][j].rgbtGreen = G;
            image[i][j].rgbtBlue = G;
        }
    }
    return;
}

// Custom function to cap the sepia colors
// Regarding the error messages in terminal I figured out the values holding by the image[i][j].rgbtR/G/B are equal to unsigned char
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
    //loop through the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //variables to hold temporary rgb values, so the other colors won't be effected
            unsigned char x = image[i][j].rgbtRed;
            unsigned char y = image[i][j].rgbtGreen;
            unsigned char z = image[i][j].rgbtBlue;

            //find the sepia values and cap them at max value 255 and assign to the pixel   
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
    //check if the image width number is odd or even
    int y = width % 2;
    //remove the remainder and divide the width to find the exit point for swap loop
    int x = (width - y) / 2;
    
    //loop through the left half and swap() the pixels with the right half ones
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
    //copy the pixels in the image 2D array
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
    
    //iterate through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //set the color values sum and divider to 0
            float sumR = 0;
            float sumG = 0;
            float sumB = 0;
            float pix = 0;
            
            //iterate through surrounding pixels of copied array
            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    //check if the surrounding pixel is in the range of 2D array of image
                    if ((i + m) >= 0 && (i + m) < height && (j + n) >= 0 && (j + n) < width)
                    {
                        sumR = sumR + blr[i + m][j + n].rgbtRed;
                        sumG = sumG + blr[i + m][j + n].rgbtGreen;
                        sumB = sumB + blr[i + m][j + n].rgbtBlue;

                        pix = pix + 1;
                    }
                }
            }
            //create variables for holding sums to prevent losing the numbers after the decimal point
            float aR = sumR / pix;
            float aG = sumG / pix;
            float aB = sumB / pix;
            
            //round the blurred average values and change the rgb values to the blurred values
            image[i][j].rgbtRed = round(aR);
            image[i][j].rgbtGreen = round(aG);
            image[i][j].rgbtBlue = round(aB);
        }
    }
    return;
}