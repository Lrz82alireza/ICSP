#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int input, i, result = 1;
    if (argc != 2)
    {
        printf("Missing Argument.\n");
        exit(EXIT_FAILURE);
    }
    input = atoi(argv[1]); /* Converting ASCII to Integer */
    for (i = 1; i <= input; ++i)
    {
        result *= i;
    }
    printf("The result is: %d\n", result);
}