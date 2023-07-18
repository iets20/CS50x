#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = 0;
    //Promt for ask the height to the user
    while (h < 1 || h > 8)
    {
        h = get_int("Height: ");
    }
    //Use for to know how many spaces we need to put to get the right-align of pyramid
    for (int i = h ; i >= 1; i--)
    {
        for (int space = 0; space < i - 1; space++)
        {
            printf(" ");
        }//Use for to create a right aligning pyramid
        for (int j = h; j >= i; j--)
        {

            printf("#");
        }// this prompt for add the gap between adjacent pyramids
        for (int space1 = 0; space1 < 2; space1++)
        {
            printf(" ");
        }//this prompt for doing the right pyramid
        for (int k = h; k >= i; k--)
        {
            printf("#");
        }
        printf("\n");
    }

}