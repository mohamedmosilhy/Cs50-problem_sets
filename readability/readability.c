#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    //get the text from the user
    string text = get_string("The text: ") ;

    //call the functions to calculate words, letters and sentences
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);
    float L, S;
    //calculate the average number of letters per 100 words in the text
    L = (letters / words) * 100 ;
    // calculate the average number of sentences per 100 words in the text.
    S = (sentences / words) * 100;
    // make rounding to the nearest integer
    int index1 = 0.0588 * L - 0.296 * S - 15.8;
    float index2 = 0.0588 * L - 0.296 * S - 15.8;
    int index;
    if ((index2 - index1) >= 0.45)
    {
        index = index1 + 1;
    }
    else
    {
        index = index1;
    }

    // different situations for the output
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

// function that return the number of the letters in the text
int count_letters(string text)
{
    int letters = 0 ;
    int n = strlen(text);
    //iterate over the text and count the letters in it
    for (int i = 0; i < n ; i++)
    {
        text[i] = tolower(text[i]);
        if (text[i] <= 'z' && text[i] >= 'a')
        {
            letters = letters + 1;
        }
    }
    return letters;
}



// function that return the number of the words in the text
int count_words(string text)
{
    int words = 1  ;
    int n = strlen(text);
    //iterate over the text and count the words in it
    for (int i = 0; i < n ; i++)
    {
        text[i] = tolower(text[i]) ;
        if (text[i] == ' ')
        {
            words = words + 1;
        }
        if ((int)text[i] == 39 && (int)text[i + 1] != 115)
        {
            words = words + 1;
        }
    }
    return words ;
}



// function that return the number of the sentences in the text
int count_sentences(string text)
{
    int sentences = 0  ;
    int n = strlen(text);
    //iterate over the text and count the sentences in it
    for (int i = 0; i < n ; i++)
    {
        text[i] = tolower(text[i]) ;
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences = sentences + 1 ;
        }
    }
    return sentences ;
}