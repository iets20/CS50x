#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = 0;
    //Prompt for ask the height to the user
    while (h < 1 || h > 8)
    {
        h = get_int("Height: ");
    }
    //Use for to know how many spaces we need to put to get the right-align of pyramid
    for (int i = h ; i >= 1; i--)
    {
        for (int space = 1; space < i ; space++)
        {
            printf(" ");
        }  //Use for to create a right aligning pyramid
        for (int j = h; j >= i; j--)
        {

            printf("#");
        }
        printf("\n");
    }

}

