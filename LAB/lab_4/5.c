#include <stdio.h>
long fib(long n);
int buffer(void);

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

    printf("%li",fib(number));

    return 1;
}


long fib(long n)
{
 if (n <= 2)
    return 1;
 return fib(n - 1) + fib (n - 2);
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