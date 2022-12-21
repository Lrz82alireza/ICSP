#include <stdio.h>

int main()
{
    int width;
    int length;

    printf("enter length and width like (5,3)\n");
    scanf("%d,%d", &width, &length);

    for (int i = 1; i <= width; i++)
    {
        for (int j = 1; j <= length; j++)
        {
            printf("%d ", i * j);
        }
        printf("\n");
    }
}