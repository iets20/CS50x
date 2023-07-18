#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // prompt to get the message from the user
    string message = get_string("Message: ");
    int binary[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};
    int quotient;
    for (int i = 0; i < strlen(message); i++)
    {
        quotient = message[i];
        //for loop in order to store the binary numbers in the arrat and divide to make the next binary number
        for (int j = 7; j >= 0; j--)
        {
            binary[j] = quotient % 2;
            quotient = quotient / 2;
        }
        for (int k = 0; k < 8; k++)
        {
            print_bulb(binary[k]);
        }
        printf("\n");

    }

}

// function that prints the dark and light emojis 
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
