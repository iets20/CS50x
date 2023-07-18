#include <stdio.h>
#include <cs50.h>

 int main(void)
 {
    //Prompting the user for a starting # of llamas
    int n;
    do
    {
        n = get_int("What's the number of llamas: ");

    } while (n < 9);

    //Prompting them for and ending # of llamas
    int g;
    do
    {
        g = get_int("Goal # of llamas: ");
    } while (g < n);
    //How many years will it take to get to the goal
    int y = 0;
    while (n < g)
    {
        n +=  n/3 -n/4;
        y++;
    }
    printf("Years: %i\n", y);
    //Every year. 1/3 of our current llamas are born and 1/4 pass away
 }