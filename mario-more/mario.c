#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int tall;
    do
    {
        //take the height from the user

        tall = get_int("height:  ");
    }
    //don't proceed until the user enters a valid number

    while (tall <= 0 || tall > 8);

    //the outer loop is for the rows
    //the inner loop is for the columns

    for (int i = 1; i <= tall; i++)
    {
        for (int j = 1; j <= 10 + i; j++)
        {
            if ((j > tall - i) && (j <= tall))
            {
                printf("#");
                continue;
            }
            if ((j > tall + 2) && (j <= tall + 2 + i))
            {
                printf("#");
                continue;
            }
            if (j <= tall + 2)
            {
                printf(" ");
            }

        }
        printf("\n");
    }
}