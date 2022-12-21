#include <stdio.h>
#define true 1
#define false 0

int main()
{
    int n, check = true;
    printf("enter the number:\n");
    scanf("%d", &n);
    /*check input*/
    if (n <= 0)
    {
        printf("number shoud be positive");
        return 1;
    }

    /*adad aval ast ya na*/
    for (int i = 3; i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            printf("%d ", i);
        }
        check = true;
    }
    return 0;
}