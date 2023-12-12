#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int nrOfLetters = count_letters(text);
    int nrOfWords = count_words(text);
    int nrOfSentences = count_sentences(text);

    float L = (float) nrOfLetters / nrOfWords * 100;
    float S = (float) nrOfSentences / nrOfWords * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Used to roundup to nearet int taking advantage of int truncation
    int grade = index + 0.5f;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Count all the letters in the given text
int count_letters(string text)
{
    int letterSum = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z')
        {
            letterSum++;
        }
    }

    return letterSum;
}

// Count all the words in the given text
int count_words(string text)
{
    int wordSum = 0;
    char prevChar = ' ';

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // handle multiple spaces in a row without addiing to words counter
        if (prevChar == ' ' && text[i] == ' ')
        {
            continue;
        }
        else if (text[i] == ' ') // nr of words in a sentence = nr of spaces +1
        {
            wordSum++;
        }
        prevChar = text[i];
    }

    // Adding 1 to the words counter if any word is found (see prev comment)
    if (wordSum != 0)
    {
        wordSum++;
    }

    return wordSum;
}

// Count all the sentences in the given text
int count_sentences(string text)
{
    int sentenceSum = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceSum++;
        }
    }

    return sentenceSum;
}
