#include <stdio.h>

int main()
{
    const int n = 5;
    int a[n];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 4; i >= 0; i--)
    {
        printf("%d", a[i]);
    }
}
