
#include "fact.h"
#include<stdlib.h>
#include<stdio.h>

int main()
{
    int n;
    printf("enter your number:");
    scanf("%d", &n);

    if (n < 0)
    {
        printf("number should be >= 0");
        return 1;
    }

    int output = 0;
    for (int i = 0; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            output += fact(i);
        }
        else
        {
            output -= fact(i);
        }
    }

    printf("%d", output);

    return 0;
}