#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    // get the number of the credit from the user
    number = get_long("please enter the number of the credit card: ");
    // getting the second-to-last digit
    long i = number / 10;
    // some variables we will use in the sum
    int counter = 0;
    int sum = 0 ;
    int first = 0;
    int second = 0;
    // Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    while (i > 0)
    {
        int last_num = i % 10;
        counter++;
        last_num = last_num * 2;
        if (last_num >= 10)
        {
            second = last_num / 10 ;
            first = last_num % 10;
            sum = first + sum + second;
            i = i / 100;
            continue;
        }
        sum = last_num + sum;
        i = i / 100;
    }

    //Add the sum to the sum of the digits that weren’t multiplied by 2.
    i = number;
    while (i > 0)
    {
        int last_num = i % 10;
        counter++;
        sum = last_num + sum ;
        i = i / 100 ;
    }
    // check for card length and starting digits
    int result1, result2, result3, result4 ;
    result1 = number / 10000000000000;
    result2 = number / 100000000000000;
    result3 = number / 1000000000000;
    result4 = number / 1000000000000000;
    if (sum % 10 == 0)
    {
        // American Express uses 15-digit numbers,All American Express numbers start with 34 or 37
        if (counter == 15 && (result1 == 34 || result1 == 37))
        {
            printf("AMEX\n");
        }
        //MasterCard uses 16-digit numbers,MasterCard numbers start with 51, 52, 53, 54, or 55
        else if (counter == 16 && (result2 == 51 || result2 == 52 || result2 == 53 || result2 == 54 || result2 == 55))
        {
            printf("MASTERCARD\n");
        }

        //Visa uses 13,all Visa numbers start with 4
        else if ((counter == 13) && (result3 == 4))
        {
            printf("VISA\n");
        }

        //Visa uses 16,all Visa numbers start with 4
        else if ((counter == 16) && (result4 == 4))
        {
            printf("VISA\n");
        }
        // if the other conditions not true then the card is invalid
        else
        {
            printf("INVALID\n");
        }

    }
    // if the total modulo 10 is not congruent to 0
    else
    {
        printf("INVALID\n");
    }


}
