#include <cs50.h>
#include <stdio.h>

long get_number();
int checksum(long number);
int card_length(long number);

int main(void)
{
    long number = get_number();
    //Variables to get what type of visa they are
    long start_digits1 = number / 100000000000000;
    long start_digits2 = number / 1000000000000000;
    long start_digits3 = number / 10000000000000;
    long start_digits4 = number / 1000000000000;
    int count = card_length(number);
    // we use this prompt to get invalid cards if they are no visas mastercard o american express(ie. diner club or discovery )
    if (checksum(number) % 10 != 0 || (start_digits1 != 51 && start_digits1 != 52 && start_digits1 != 53 && start_digits1 != 54
                                       && start_digits1 != 55 && start_digits3 != 34 && start_digits3 != 37 && start_digits2 != 4 && start_digits4 != 4))
    {
        printf("INVALID\n");
    }
    else
    {
        //Mastercard or visa 16 digits
        if (count == 16)
        {
            start_digits1 = number / 100000000000000;
            if (start_digits1 == 51 || start_digits1 == 52 || start_digits1 == 53 || start_digits1 == 54 || start_digits1 == 55)
            {
                printf("MASTERCARD\n");
            }
            start_digits2 = number / 1000000000000000;
            if (start_digits2 == 4)
            {
                printf("VISA\n");
            }
        }
        //American express 15 digits
        if (count == 15)
        {
            start_digits3 = number / 10000000000000;
            if (start_digits3 == 34 || start_digits3 == 37)
            {
                printf("AMEX\n");
            }
        }
        //Visa of 13 digits
        if (count == 13)
        {
            start_digits4 = number / 1000000000000;
            if (start_digits4 == 4)
            {
                printf("VISA\n");
            }
        }
    }

}
//Prompt to get credit card number
long get_number(void)
{
    long number = get_long("Number: ");
    return number;
}
// Luhn's Algorithm
int checksum(long number)
{
    long n;
    int remainder;
    int sum;
    int sum1 = 0;
    int sum2 = 0;
    long number1 = number;
    while (number > 0)
    {
//Prompt to separate and multiply every other digit by 2, starting with the number's second-to last digit
        n = ((number / 10) % 10) * 2;
        while (n > 0)
        {
            remainder = n % 10;
            sum1 += remainder; //Adding those product's digits together
            n /= 10;
        }
        number /= 100;
    }
    //we this prompt we get the number that we dont multiply by 2 of the card
    number = number1;
    remainder = 0;
    while (number > 0)
    {
        n = (number % 10);
        remainder = n % 10;
        sum2 += remainder;
        number /= 100;
    }
    //Adding digits number together plus numbers we didnt multiply by 2
    sum = sum1 + sum2;
    return sum;
}
//Length of the card number
int card_length(long number)
{
    int count = 0;
    while (number > 0)
    {
        count += 1;
        number /= 10;
    }
    return count;
}
