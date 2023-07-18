#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int cl, int cw, int cs);

int main(void)
{
    //Gets some text input from the user and prints it back out
    string text = get_string("Text: ");
    int c = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);
    int index = coleman_liau(c, w, s);
    //We define which grades belong the text
    if (index < 16 && index > 0)
    {
        printf("Grade %i\n", index);
    }
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
}
//letter count function
int count_letters(string text)
{
    int cl = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            cl++;
        }
    }
    return cl;
}

//words count function
int count_words(string text)
{
    int cw = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (isspace(text[i]))
        {
            cw++;
        }

    }
    if (text[n - 1] == '.' || text[n - 1] == '?' || text[n - 1] == '!')
    {
        cw++;
    }
    return cw;
}
//count of sentences
int count_sentences(string text)
{
    int cs = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            cs++;
        }
    }
    if (cs == 0)
    {
        cs++;
    }
    return cs;
}
//Coleman-Liau index formula
int coleman_liau(int cl, int cw, int cs)
{
    double L = (cl * 100.0) / cw;
    double S = (cs * 100.0) / cw;
    double index = (0.0588 * L) - (0.296 * S) - 15.8;
    int cole_liau = (int) round(index);

    return cole_liau;
}