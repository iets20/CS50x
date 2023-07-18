#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get_string to recall a variable
    string name = get_string("What's your name? \n");
    //Perform the action with the variable we recall
    printf("Hello, %s\n", name);

}