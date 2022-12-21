#include <stdio.h>

int main()
{
    char arr[5] = "hello";
    int counter = 0;
    for (int i = 0; i < 5; i++)
    {
        if (arr[5] != '\0')
        {
            counter++;
        }
    }

    printf("%i", counter);
}