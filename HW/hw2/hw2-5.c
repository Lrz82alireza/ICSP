#include <stdio.h>

int main()
{
    int n1, n2, yn1, yn2; /*yekan n1 = yn1, yekan n2 = yn2*/
    printf("enter two numbers like(5,3)\n");
    scanf("%d,%d", &n1, &n2);

    /*check inputs*/
    if (n1 <= 0 || n2 <= 0)
    {
        printf("numbers should be positive\n");
        return 1;
    }
    if (n1 % 10 == 1 || n2 % 10 == 1)
    {
        printf("true\n");
        return 0;
    }
    else if (n1 % 10 > n2 % 10)
    {
        yn1 = n1 % 10;
        yn2 = n2 % 10;
    }
    else if (n1 % 10 < n2 % 10)
    {
        yn1 = n2 % 10;
        yn2 = n1 % 10;
    }
    else            /*yn1 = yn2*/
    {
        printf("true\n");
        return 0;
    }

    /*do numbers have common factor??*/
    for (int i = 2; i <= yn1; i++)
    {
        if (yn1 % i == 0 && yn2 % i == 0)
        {
            printf("true\n");
            return 0;
        }
    }
    /*numbers dont have common factor*/
    printf("false\n");
    return 0;
}