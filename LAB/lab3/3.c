#include <stdio.h>

int main()
{
    int m;

    printf("enter height:\n");
    scanf("%d", &m);
    if (m % 2 == 0)
    {
        printf("height should be odd\n");
        return 1;
    }
    
    int Height = (m + 1) / 2;

    for (int i = 1; i <= Height; i++)
    {
        for (int k = 0; k < Height - i; k++)
        {
            printf("-");
        }

        for (int k = 1; k <= ((i - 1) * 2) + 1; k++)
        {
            printf("*");
        }

        for (int k = 0; k < Height - i; k++)
        {
            printf("-");
        }
        printf("\n");
    }
}
