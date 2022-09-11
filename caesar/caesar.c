#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char rotate(char x, int k);
bool only_digit(string x);

int main(int argc, string argv[])
{
    // program must accept a non-negative integer.
    if (argv[1] < 0)
    {
        return 1;
    }
    // program must accept a single command-line argument.
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // program must accept a single command-line argument.
    if (only_digit(argv[1]) != 1)
    {
        printf("Usage: ./caesar key\n");
        return 1 ;
    }
    // Convert argv[1] from a `string` to an `int`
    int k = atoi(argv[1]) ;
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ") ;
    int n = strlen(plaintext);
    // Rotate every character in plaintext
    for (int i = 0; i < n ; i++)
    {
        plaintext[i] = rotate(plaintext[i], k);
    }

    printf("ciphertext: %s\n", plaintext);
}

// Make sure every character in argv[1] is a digit
bool only_digit(string x)
{
    int n = strlen(x);
    for (int i = 0 ; i < n; i++)
    {
        if (x[i] <= '9' && x[i] >= '0')
        {
            continue ;
        }
        else
        {
            return 0 ;
        }
    }
    return 1 ;
}

char rotate(char x, int k)
{
    int a, b;
    // dealing with the case of entering a key which is greater than 26
    while (k > 26)
    {
        k = k - 26 ;
    }
    // rotating using the formula : c = (p + k) % 26
    if ((x <= 'Z' && x >= 'A'))
    {
        b = (int) x - 65 ;
        a = (b + k) % 26 ;
        a = a + 65 ;
        a = (char) a;
        return a ;
    }
    if ((x <= 'z' && x >= 'a'))
    {
        b = (int) x - 97 ;
        a = (b + k) % 26 ;
        a = a + 97 ;
        a = (char) a;
        return a ;
    }
    else
    {
        return x;
    }
}