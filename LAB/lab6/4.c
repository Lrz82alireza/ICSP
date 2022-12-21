#include <stdio.h>

int compare(char *first_array, char *second_array);

int main()
{
    char first_array[70], second_array[70];
    scanf("%s", first_array);
    scanf("%s", second_array);
    compare(first_array, second_array);
}

int compare(char *first_array, char *second_array)
{
    for (int i = 0; i < 70 && (*(first_array + i) != '\0' || *(second_array + i) != '\0'); i++)
    {
        if (*(first_array + i) != *(second_array + i))
        {
            printf("False");
            return 0;
        }
    }
    printf("true");
    return 1;
}