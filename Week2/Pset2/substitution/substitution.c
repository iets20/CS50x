#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char encrypt(char c, char key);
int position_key(char c);
bool valid_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!valid_key(argv[1]))
    {
        return 1;
    }
    else
    {
        string key = argv[1];
        string plaintext = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            int x = position_key(plaintext[i]);
            printf("%c", encrypt(plaintext[i], key[x]));
        }
        printf("\n");
        return 0;
    }
}

char encrypt(char c, char key)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            if (!isupper(key))
            {
                key = toupper(key);
            }
            c = key;
        }
        else
        {
            if (!islower(key))
            {
                key = tolower(key);
            }
            c = key;
        }
    }
    return c;
}

int position_key(char c)
{
    // we see if its a alphabetical character
    if (isalpha(c))
    {
        //if its Uppercase
        if (isupper(c))
        {
            c = ((c - 'A') % 26);
        }
        //if its Lowercase
        if (islower(c))
        {
            c = ((c - 'a') % 26);
        }
    }
    //if its not a alphabetical character we just return the same char
    else
    {
        return c;
    }

    return (int)c;
}
bool valid_key(string key)
{
    for (int k = 0; k < strlen(key); k++)
    {
        if (!isalpha(key[k]))
        {
            return false;
        }
    }

    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}