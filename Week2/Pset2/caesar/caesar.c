#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string x);
char rotate(char c, int i);

int main(int argc, string argv[])
{
    //Discard invalid inputs take in account that we only need two strings
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //we use the function to know if its a non-negative number
        if (only_digits(argv[1]) == 0)
        {
            //we convert the string into a integer
            int key = atoi(argv[1]);
            // get the for the user the text which wants to be encrypted
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            //we use for to count each character of the text and printf
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                //we the function rotate we get the ciphertext
                printf("%c", rotate(plaintext[i], key));
            }
            printf("\n");
        }
        else
        {
            //Discard invalid inputs
            return 1;
        }
    }

}

//Get a bool answer 0 for true and 1 for false if the string which will be the key is a non-negative number
bool only_digits(string x)
{
    for (int i = 0; i < strlen(x); i++)
    {
        if (!isdigit(x[i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }
    return 0;
}
//with this function we rotate the char by as many positions as the key indicates
char rotate(char c, int i)
{
    // we see if its a alphabetical character
    if (isalpha(c))
    {
        //if its Uppercase
        if (isupper(c))
        {
            c = ((c - 'A' + i) % 26 + 'A');
        }
        //if its Lowercase
        if (islower(c))
        {
            c = ((c - 'a' + i) % 26 + 'a');
        }
    }
    //if its not a alphabetical character we just return the same char
    else
    {
        return c;
    }

    return c;
}