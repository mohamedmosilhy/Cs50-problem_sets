#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get the name from the user
    string name = get_string("enter your name please: ");
    //print the message and the name
    printf("hello, %s\n", name);
}