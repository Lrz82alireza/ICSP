#include <string.h>
#include <stdio.h>

int main ()
{
    char first_array[70], second_array[70];
    scanf("%s", first_array);
    scanf("%s", second_array);

    if (!strcmp(first_array, second_array))
    {
        printf("number of charecters: %d", strlen(first_array));
        return 1;
    }
    strcpy(first_array, second_array);
    return 0;
}