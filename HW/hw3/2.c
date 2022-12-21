#include <stdio.h>

int pow(int a, int b); // a^b
int size(int number);
int compare(int n1, int n2);

int main()
{
    /*get input*/
    int n1, n2;
    scanf("%d,%d", &n1, &n2);

    compare(n1, n2);
    return 0;
}

int size(int number) // size of number
{
    int counter = 0;
    while (number >= 1)
    {
        number /= 10;
        counter++;
    }
    return counter;
}

int pow(int a, int b) // a^b
{
    int output = 1;
    for (int i = 1; i <= b; i++)
    {
        output *= a;
    }
    return output;
}

int compare(int n1, int n2)
{
    /*check input sizes be equal*/
    if (size(n1) != size(n2))
    {
        printf("NO");
        return 1;
    }
    int sizen = size(n1);

    /*check equalation of digits*/
    for (int i = 0; i < sizen; i++)
    {
        if ((n1 % pow(10, (sizen - i))) / pow(10, (sizen - i - 1)) != (n2 % pow(10, (i + 1))) / pow(10, i))
        {
            printf("NO\n");
            return 1;
        }
    }
    printf("YES\n");
}