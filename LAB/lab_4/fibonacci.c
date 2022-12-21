#include <stdio.h>
long fibonacci(long n);
int buffer(void);

long loutput = 0;

int main()
{
    /*get input*/
    int number = 0;

    do
    {
        printf("enter your number:");
        scanf("%d", &number);
    }
    while (buffer());

    /*check input*/
    if (number < 0)
    {
        printf("number should be > 0\n");
        return 0;
    }

    printf("%li",fibonacci(number));

    return 1;
}

long fibonacci(long n)
{
    if (n <= 2)
    {
        loutput += 1;
    }
    else
    {
        fibonacci(n-1);
        fibonacci(n-2);
    }
}

/*make buffer free*/
int buffer(void)
{
    int output = 0;
    while (getchar() != '\n')
    {
        output = 1;
    }
    return output;
}