#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //iterar sobre cada pixel, recordar tambien es importante que un array ya cuenta como puntero, si creo un pixel= image[i][j]
            //estoy haciendoi una copia no cambiando el original
            if (image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00)
            {
                image[i][j].rgbtBlue = 0x00;
                image[i][j].rgbtRed = 0xff;
                image[i][j].rgbtGreen = 0xff;
            }
        }
    }
}
