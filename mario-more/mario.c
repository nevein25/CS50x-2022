#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // Prompt user for height
    do
    {
        height = get_int("Enter Height: ");

    }
    while (!(height > 0 && height < 9));

    // Iteration for number of lines
    for (int i = 1 ; i <= height ; i++)
    {

        // first triangle
        // Iteration for number of spaces
        for (int s = height - i ; s > 0 ; s--)
        {
            printf(" ");
        }
        // Iteration for number of #
        for (int j = 1 ; j <= i ; j++)
        {
            printf("#");
        }

        printf("  ");
        // Second triangle
        // Iteration for number of #
        for (int j = 1 ; j <= i ; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}