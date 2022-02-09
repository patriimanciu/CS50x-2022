#include <stdio.h>
#include <cs50.h>

bool is_valid(long number);
int is_mastercard(long number);
int is_visa(long number);
int is_amex(long number);
int nr_digits(long number);

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    if (is_valid(number))
    {
        //checks if the cards are valid by the number of digits, calling each function when needed
        int digits = nr_digits(number);
        if(digits == 15)
        {
            if (is_amex(number) == 1)
            {
                printf("AMEX\n");
            }
            else
                printf("INVALID\n");
        }
        else if (digits == 13)
        {
            if (is_visa(number) == 1)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 16)
        {
            if (is_visa(number) == 1)
            {
                printf("VISA\n");
            }
            else if (is_mastercard(number) == 1)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool is_valid(long number)
{
    int summ = 0; //every other number from second-to-last
    int sum2 = 0; //all other numbers
    int i = 0; // if (i % 2 == 1) sum2; else summ;
    int c; //last digit
    while (number)
    {
        i++;
        c = number % 10;
        //adds to sum2 all the numbers on odd positions
        if (i % 2)
        {
            sum2 += c;
        }
        else
        {
            //multiplies the digits by 2 and adds them together
            c *= 2;
            if (c > 9)
            {
                while (c)
                {
                    summ += c % 10;
                    c /= 10;
                }
            }
            else
            {
                summ += c;
            }
        }
        number /= 10;
    }
    //If the summ's last digit is 0 the card is valid
    if ((summ + sum2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int nr_digits(long number)
{
    int dig = 0; //counter for the number of digits
    while (number)
    {
        dig++;
        number /= 10;
    }
    return dig;
}

int is_mastercard(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    if (number / 10 == 5)
    {
        if (number % 10 == 1 || number % 10 == 2 || number % 10 == 3 || number % 10 == 4 || number % 10 == 5)
        {
            return 1;
        }
    }
    return 0;
}

int is_visa(long number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    if(number % 10 == 4)
    {
        return 1;
    }
    return 0;
}

int is_amex(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    if(number / 10 == 3)
    {
        if(number % 10 == 4 || number % 10 == 7)
        {
            return 1;
        }
    }
    return 0;
}