#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char a, int key);

int main(int argc, string argv[])
{
    //If there are too many command-line arguments, returns 1
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //If the arguments is int
        if (only_digits(argv[1]))
        {
            //Converting the given key into an int variable
            int key = atoi(argv[1]);
            printf("key: %i\n", key);

            //Get user input
            string text = get_string("plaintext: ");

            int n = strlen(text);
            printf("ciphertext: ");

            //Call the rotate function for each char
            for (int i = 0; i < n; i++)
            {
                printf("%c", rotate(text[i], key));
            }
            printf("\n");
            return 0;
        }
        //If the argument is not an integer, returns 1
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
}

bool only_digits(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        //We use the function isdigit to see if the current char is 0 - 9
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char a, int key)
{
    //If the current char is uppercase, we use the given formula and rotate the char, using A = 0;
    if (isupper(a))
    {
        char new = ((int) a - 65 + key) % 26;
        return new + 65;
    }

    //Handled the same way as uppercase, just with different rotation
    else if (islower(a))
    {
        char new = ((int) a - 97 + key) % 26;
        return new + 97;
    }
    else
    {
        return a;
    }
}