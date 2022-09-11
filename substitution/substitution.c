#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool only_characters(string x);
bool is_repeated(string x);
char rotate(string key, char plaintext);

int main(int argc, string argv[])
{
    // program must accept a single command-line argument.
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // the key's characters must be 26 .
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // the key must not contain any non_alphabetic characters
    if (only_characters(argv[1]) == false)
    {
        printf("key must contain alphabetic characters\n");
        return 1;
    }
    //the key must not contain repeated characters
    if (is_repeated(argv[1]))
    {
        printf("key must not contain repeated characters\n");
        return 1;
    }
    //get the plaintext form the user and calculate the length of it
    string plaintext = get_string("plaintext: ") ;
    int n = strlen(plaintext);
    // Rotate every character in plaintext
    for (int i = 0; i < n ; i++)
    {
        plaintext[i] = rotate(argv[1], plaintext[i]);
    }

    printf("ciphertext: %s\n", plaintext);


}




// function that take the key and check if it has only characters or not
bool only_characters(string x)
{
    int n = strlen(x);
    //rotate over the key and check if the character is in the alphabet or not
    for (int i = 0; i < n; i++)
    {
        if ((x[i] <= 'Z' && x[i] >= 'A') || (x[i] <= 'z' && x[i] >= 'a'))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;

}
// function that take the key to check if it has repeated charcters or not
bool is_repeated(string x)
{
    int n = strlen(x);
    // iterate over the key with 2 loops the first makes us take one character and with the second loop
    // we iterate over the key to check if the character is repeated
    for (int i = 0; i < n; i++)
    {
        char b =  tolower(x[i]);
        for (int j = 1; j <= n; j++)
        {
            if (j == i)
            {
                continue;
            }
            char a =  tolower(x[j]);
            if (b == a)
            {
                return 1;
            }
            else
            {
                continue;
            }
        }
    }

    return 0;
}

// function that take a character from the plaintext and rotate it
char rotate(string key, char plaintext)
{
    if ((plaintext <= 'Z' && plaintext >= 'A'))
    {
        int a = (int) plaintext - 65 ;
        plaintext = key[a];
        return toupper(plaintext);
    }

    if ((plaintext <= 'z' && plaintext >= 'a'))
    {
        int a = (int) plaintext - 97 ;
        plaintext = key[a];
        return tolower(plaintext);
    }
    else
    {
        return plaintext;
    }

}