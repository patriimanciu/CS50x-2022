#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //line
    for (int i = 0; i < n; i++)
    {
        //column
        for (int j = 0; j < n; j++)
        {
            //print the left side of the pyramid
            if (j >= n - i - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("  ");
        for (int j = 0; j < n; j++)
        {
            //print the right side of the pyramid
            if (i >= j)
            {
                printf("#");
            }
            else
            {
                printf("\n");
                break;
            }
        }
    }
    printf("\n");
}