#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            int grayscale = round((pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue) / 3.0);

            pixel->rgbtRed = grayscale;
            pixel->rgbtBlue = grayscale;
            pixel->rgbtGreen = grayscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *left_pixel = &image[i][j];
            RGBTRIPLE *right_pixel = &image[i][width - j -1];

            RGBTRIPLE temp = *left_pixel;

            *left_pixel = *right_pixel;
            *right_pixel = temp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create copy image to be referenced while updating original
    RGBTRIPLE(*copy_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    // iterate over each pixel in the original image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // define box limits to calculate avg
            int init_i = i - 1, stop_i = i + 1, init_j = j - 1, stop_j = j + 1;
            if (init_i < 0)
            {
                init_i = 0;
            }
            if (stop_i == height)
            {
                stop_i = height - 1;
            }
            if (init_j < 0)
            {
                init_j = 0;
            }
            if (stop_j == width)
            {
                stop_j = width - 1;
            }

            // iterate over limits for each pixel and gets avg for each color in copy pixel
            int count = 0, count_red = 0, count_green = 0, count_blue = 0;
            for (int k = init_i; k < stop_i + 1; k++)
            {
                for (int l = init_j; l < stop_j + 1; l++)
                {
                    RGBTRIPLE copy_pixel = copy_image[k][l];
                    count_red += copy_pixel.rgbtRed;
                    count_green += copy_pixel.rgbtGreen;
                    count_blue += copy_pixel.rgbtBlue;
                    count++;
                }
            }
            // assign avg color to the original pixel
            pixel->rgbtRed = round(count_red / (float) count);
            pixel->rgbtGreen = round(count_green / (float) count);
            pixel->rgbtBlue = round(count_blue / (float) count);
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy image to be reference while updating original
    RGBTRIPLE(*copy_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    // create gx and gy
    const int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // iterate over each pixel in the original image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // define limits to calculate box
            int init_i = i - 1, stop_i = i + 1, init_j = j - 1, stop_j = j + 1;
            if (init_i < 0)
            {
                init_i = 0;
            }
            if (stop_i == height)
            {
                stop_i = height - 1;
            }
            if (init_j < 0)
            {
                init_j = 0;
            }
            if (stop_j == width)
            {
                stop_j = width - 1;
            }


            int count_red_x = 0, count_green_x = 0, count_blue_x = 0, count_red_y = 0, count_green_y = 0, count_blue_y = 0;
            for (int k = init_i; k < stop_i + 1; k++)
            {
                for (int l = init_j; l < stop_j + 1; l++)
                {
                    RGBTRIPLE copy_pixel = copy_image[k][l];
                    count_red_x += copy_pixel.rgbtRed * gx[k - i + 1][l - j + 1];
                    count_green_x += copy_pixel.rgbtGreen * gx[k - i + 1][l - j + 1];
                    count_blue_x += copy_pixel.rgbtBlue * gx[k - i + 1][l - j + 1];

                    count_red_y += copy_pixel.rgbtRed * gy[k - i + 1][l - j + 1];
                    count_green_y += copy_pixel.rgbtGreen * gy[k - i + 1][l - j + 1];
                    count_blue_y += copy_pixel.rgbtBlue * gy[k - i + 1][l - j + 1];
                }
            }
            long total_red = round(sqrt(pow(count_red_x, 2) + pow(count_red_y, 2)));
            long total_green = round(sqrt(pow(count_green_x, 2) + pow(count_green_y, 2)));
            long total_blue = round(sqrt(pow(count_blue_x, 2) + pow(count_blue_y, 2)));

            pixel->rgbtRed = 255;
            pixel->rgbtGreen = 255;
            pixel->rgbtBlue = 255;

            if (total_red < 255)
            {
                pixel->rgbtRed = total_red;
            }
            if (total_green < 255)
            {
                pixel->rgbtGreen = total_green;
            }
            if (total_blue < 255)
            {
                pixel->rgbtBlue = total_blue;
            }
        }
    }
    return;
}
