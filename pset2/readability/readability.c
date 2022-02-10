#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    //Letters per 100 words
    float L = (float) letters / words * 100;

    //Sentences per 100 words
    float S = (float) sentences / words * 100;

    //the Coleman-Liau index
    float idx = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(idx);

    //Grades 1-16, before grade 1 and grade 16+ printing
    if (index < 1)
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

int count_letters(string text)
{
    int lenght = strlen(text);
    int count = 0;
    for (int i = 0; i < lenght; i++)
    {
        //If the character is a letter, counter increases by 1
        if (islower(text[i]) || isupper(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    int lenght = strlen(text);
    for (int i = 0; i < lenght; i++)
    {
        //If the index is a ' ', it increases the words counter
        if (text[i] == ' ')
        {
            count++;
        }
        //If the index is on a special character, i also increases by one to prevent the error
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
            i++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    int lenght = strlen(text);
    for (int i = 0; i < lenght; i++)
    {
        //Counter increases each time there is a special character
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}