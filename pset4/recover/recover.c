#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#define BLOCK_SIZE 512
#define NAME 8

typedef uint8_t BYTE;

bool new_jpeg(BYTE copy[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    //error message if the usage doesn't corespond (more or less than 2 command line arguments)
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //opening and creating in and out files
    FILE *file_in = fopen(argv[1], "r");
    FILE *file_out;

    if (file_in == NULL)
    {
        printf("Error: File cannot be opened\n");
        return 1;
    }

    //create a buffer
    BYTE copy[BLOCK_SIZE];

    bool first_jpeg = false;

    int index = 0;

    //for as long as you can read from the in file
    while (fread(copy, BLOCK_SIZE, 1, file_in))
    {
        //checks if there had been found a new jpeg header
        if (new_jpeg(copy))
        {
            //if this is not the first jpeg
            if (!first_jpeg)
            {
                first_jpeg = true;
            }
            else
            {
                fclose(file_out);
            }

            char name[NAME];

            //generates the file names into the name variable
            sprintf(name, "%03i.jpg", index++);

            //gives the file the generated name
            file_out = fopen(name, "w");

            //writes the previous file we have stored in the buffer (copy)
            fwrite(copy, BLOCK_SIZE, 1, file_out);
            if (file_out == NULL)
            {
                printf("Error: File connot be written in\n");
                return 1;
            }
        }
        else if (first_jpeg)
        {
            //if this is not the first jpeg write it directly
            fwrite(copy, BLOCK_SIZE, 1, file_out);
        }
    }
    fclose(file_out);
    fclose(file_in);
}

bool new_jpeg(BYTE copy[])
{
    //checks for the header of a jpeg file
    if (copy[0] == 0xff && copy[1] == 0xd8 && copy[2] == 0xff && (copy[3] & 0xf0) == 0xe0)
    {
        return 1;
    }
    return 0;
}