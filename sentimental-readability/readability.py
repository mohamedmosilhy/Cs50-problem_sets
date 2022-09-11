from cs50 import get_string


def main():
    # get the text from the user
    text = get_string("The text: ")
    # call the functions to calculate words, letters and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    # calculate the average number of letters per 100 words in the text
    L = (letters / words) * 100
    # calculate the average number of sentences per 100 words in the text.
    S = (sentences / words) * 100
    # make rounding to the nearest integer
    index1 = int(0.0588 * L - 0.296 * S - 15.8)
    index2 = 0.0588 * L - 0.296 * S - 15.8
    if (index2 - index1) >= 0.45:
        index = index1 + 1
    else:
        index = index1
    # different situations for the output
    if index < 0:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# function that return the number of the letters in the text
def count_letters(text):
    letters = 0
    n = len(text)
    text = text.lower()
    # iterate over the text and count the letters in it
    for i in range(n):
        if (text[i] <= 'z' and text[i] >= 'a'):
            letters = letters + 1
    return letters


# function that return the number of the words in the text
def count_words(text):
    words = 1
    n = len(text)
    text = text.lower()
    # iterate over the text and count the words in it
    for i in range(n):
        if text[i] == ' ':
            words = words + 1
        if (ord(text[i]) == 39 and ord(text[i + 1]) != 115):
            words = words + 1

    return words


# function that return the number of the sentences in the text
def count_sentences(text):
    sentences = 0
    n = len(text)
    text = text.lower()
    # iterate over the text and count the sentences in it
    for i in range(n):
        if text[i] in ['.', '!', '?']:
            sentences = sentences + 1
    return sentences


main()