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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
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
            pixel[i][j] = image[i][j];
        }
    }
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
