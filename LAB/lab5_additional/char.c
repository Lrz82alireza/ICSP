#include <stdio.h>

int strlen(char *input);
int tolower(char input);
int toupper(char input);

int main()
{
    /*get inputs*/
    char input[5][21];
    for (int i = 0; i < 5; i++)
    {
        scanf("%s", input[i]);
    }

    for (int i = 1; i < 5; i++)
    {
        for (int j = 0; j < strlen(input[i]); j++)
        {
            for (int k = 0; k < strlen(input[0]); k++)
            {
                if (input[i][j] == tolower(input[0][k]) || input[i][j] == toupper(input[0][k]))
                {
                    input[i][j] = '$';
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", input[i]);
    }
}

int toupper(char input)
{
    if (97 <= input && input <= 122) // lower
    {
        input = input - 32;
    }
    return input;
}

int tolower(char input)
{
    if (65 <= input && input <= 90) // upper
    {
        input = input + 32;
    }
    return input;
}

int strlen(char *input)
{
    int i = 0;
    while (input[i] != '\0')
    {
        i++;
    }
    return i;
}