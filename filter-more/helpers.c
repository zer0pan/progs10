#include "helpers.h"
#include <stdlib.h>
#include <math.h>

int avrg(int sum);
int sq(int num);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int num;
    float avg;
    int test;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            test = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            if (avg - test > 0.5)
            {
                num = test + 1;
            }
            else
            {
                num = test;
            }
            image[i][j].rgbtBlue = num;
            image[i][j].rgbtGreen = num;
            image[i][j].rgbtRed = num;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2; // 270 degree rotation
    //  int half2 = height / 2; // 270 degree rotation
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    /*for (int i = 0; i < half2; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp = image[i][j];
            image[i][j] = image[height - 1 - i][j];
            image[height - 1 - i][j] = temp;
        }
    }*/
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary image[height][width]
    RGBTRIPLE **temp = malloc(height * sizeof(RGBTRIPLE *));
    for (int i = 0; i < height; i++)
    {
        temp[i] = malloc(width * sizeof(RGBTRIPLE));
    }
    int blue;
    int red;
    int green;
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            red = 0;
            blue = 0;
            green = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    red += image[k][l].rgbtRed;
                    blue += image[k][l].rgbtBlue;
                    green += image[k][l].rgbtGreen;
                }
            }
            temp[i][j].rgbtRed = avrg(red);
            temp[i][j].rgbtBlue = avrg(blue);
            temp[i][j].rgbtGreen = avrg(green);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
        free(temp[i]); // Free each row
    }

    free(temp); // Free array of pointers
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE **temp = malloc(height * sizeof(RGBTRIPLE *));
    for (int i = 0; i < height; i++)
    {
        temp[i] = malloc(width * sizeof(RGBTRIPLE));
    }

    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int blue = 0;
            int red = 0;
            int green = 0;

            int blue1 = 0;
            int red1 = 0;
            int green1 = 0;

            int matx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int maty[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            int counti = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                int countj = 0;
                for (int l = j - 1; l <= j + 1; l++)
                {
                    red += image[k][l].rgbtRed * matx[counti][countj];
                    red1 += image[k][l].rgbtRed * maty[counti][countj];
                    green += image[k][l].rgbtGreen * matx[counti][countj];
                    green1 += image[k][l].rgbtGreen * maty[counti][countj];
                    blue += image[k][l].rgbtBlue * matx[counti][countj];
                    blue1 += image[k][l].rgbtBlue * maty[counti][countj];

                    countj++;
                }
                counti++;
            }

            temp[i][j].rgbtRed = round(sqrt((double)(sq(red) + sq(red1))));
            temp[i][j].rgbtBlue = round(sqrt((double)(sq(green) + sq(green1))));
            temp[i][j].rgbtGreen = round(sqrt((double)(sq(blue) + sq(blue1))));
        }
    }

    // ___________________________________________________________________
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
        free(temp[i]); // Free each row
    }

    free(temp); // Free array of pointers
    return;
}

int avrg(int sum)
{
    int num;
    int test = sum / 9;
    float avg = sum / 9.0;
    if (avg - test > 0.5)
    {
        num = test + 1;
    }
    else
    {
        num = test;
    }
}

int sq(int num)
{
    return num * num;
}