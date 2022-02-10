#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool only_chars(string s);
int rotate(char a);
bool duplicates(string s);

int main(int argc, string argv[])
{
    //If we get too much input, return 1
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //If the input consists only of characters
        if (only_chars(argv[1]))
        {
            //Lenght must be 26 for every letter of the alphabet
            if (strlen(argv[1]) != 26)
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }

            //The key should not contain duplicates
            else if (!duplicates(argv[1]))
            {
                printf("Key must contain 26 DIFFERENT characters.\n");
                return 1;
            }
            else
            {
                string text = get_string("plaintext: ");

                int n = strlen(text);
                printf("ciphertext: ");

                for (int i = 0; i < n; i++)
                {
                    //Output must be in the same case as the input!
                    int current = rotate(text[i]);
                    if (current == -1)
                    {
                        printf("%c", text[i]);
                    }
                    else if (isupper(argv[1][current]) == isupper(text[i]))
                    {
                        printf("%c", argv[1][current]);
                    }
                    else
                    {
                        //Another rotation to match the output with the input's case
                        if (isupper(text[i]))
                        {
                            printf("%c", argv[1][current] - 97 + 65);
                        }
                        else
                        {
                            printf("%c", argv[1][current] + 97 - 65);
                        }
                    }
                }
                printf("\n");

                return 0;
            }
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
}

bool only_chars(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        //We use the functions isupper and islower to see if the current char is a character
        if (!isupper(s[i]) && !islower(s[i]))
        {
            return false;
        }
    }
    return true;
}

int rotate(char a)
{
    //Rotation is done by case
    if (isupper(a))
    {
        char new = (int) a - 65;
        return new;
    }
    else if (islower(a))
    {
        char new = (int) a - 97;
        return new;
    }
    else
        //If the current s[i] is not a character, return -1 to prevent it from rotating
    {
        return -1;
    }
}

bool duplicates(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            //When it finds a duplicate it returns false and the funtion stops
            if (s[i] == s[j])
            {
                return false;
            }
        }
    }
    return true;
}