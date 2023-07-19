#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        int ref = width - 1;
        for (int j = 0; j < width; j++)
        {
            image[i][j] = pixel[i][ref];
            ref--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0, green = 0, blue = 0;
            float counter = 0;
            //for the neighborhood in the row
            for (int r = -1; r < 2;  r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    //con esto nos cuidamos de no salirnos de las filas
                    // es decir si tocamos una fila que no existe nos saltamos esa iteracion
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    // con esto de no salirnos de las columnas
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    red += image[i + r][j + c].rgbtRed;
                    blue += image[i + r][j + c].rgbtBlue;
                    green += image[i + r][j + c].rgbtGreen;
                    counter++;
                }
            }
            //copiamos la imagen blurreada a la copia para no afectar el blur de los siguientes pixeles
            pixel[i][j].rgbtRed = round(red / counter);
            pixel[i][j].rgbtBlue = round(blue / counter);
            pixel[i][j].rgbtGreen = round(green / counter);
        }
    }

    //imprimimos los pixeles
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = pixel[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Create an copy with black border 1 pixel more bigger than the actual image
    RGBTRIPLE temp[height + 2][width + 2];
    //copy the internal image without taking in account the borders
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            temp[i][j] = image[i - 1][j - 1];
        }
    }
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            //fill the borders with black pixels
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
                temp[i][j].rgbtRed = 0;
                temp[i][j].rgbtGreen = 0;
                temp[i][j].rgbtBlue = 0;
            }
        }
    }
    //create 2 matrix of gx and gy
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //create matrix that stores each color per pixel
    int red_pixel[3][3], blue_pixel[3][3], green_pixel[3][3];
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    //stores the color matrix of each pixel
                    red_pixel[1 + r][1 + c] = temp[i + r][j + c].rgbtRed;
                    blue_pixel[1 + r][1 + c] = temp[i + r][j + c].rgbtBlue;
                    green_pixel[1 + r][1 + c] = temp[i + r][j + c].rgbtGreen;
                }
            }
            // variable that helps us to get a weighted sum of the values per color
            int sum_rgx = 0, sum_rgy = 0, sum_bgx = 0, sum_bgy = 0, sum_ggx = 0, sum_ggy = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3 ; l++)
                {

                    sum_rgx += gx[k][l] * red_pixel[k][l];
                    sum_rgy += gy[k][l] * red_pixel[k][l];
                    sum_bgx += gx[k][l] * blue_pixel[k][l];
                    sum_bgy += gy[k][l] * blue_pixel[k][l];
                    sum_ggx += gx[k][l] * green_pixel[k][l];
                    sum_ggy += gy[k][l] * green_pixel[k][l];
                }
            }
            //set the new color in the original image
            image[i - 1][j - 1].rgbtRed = (round(sqrt(pow(sum_rgx, 2) + pow(sum_rgy, 2))) > 255) ? 255 : round(sqrt(pow(sum_rgx,
                                          2) + pow(sum_rgy, 2)));

            image[i - 1][j - 1].rgbtBlue = (round(sqrt(pow(sum_bgx, 2) + pow(sum_bgy, 2))) > 255) ? 255 : round(sqrt(pow(sum_bgx,
                                           2) + pow(sum_bgy, 2)));

            image[i - 1][j - 1].rgbtGreen = (round(sqrt(pow(sum_ggx, 2) + pow(sum_ggy, 2))) > 255) ? 255 : round(sqrt(pow(sum_ggx,
                                            2) + pow(sum_ggy, 2)));
        }
    }
    return;
}
