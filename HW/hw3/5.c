#include <stdio.h>
long fibonacci(long n);

int main()
{
    /*get input*/
    int number = 0;
    scanf("%d", &number);

    printf("%li", fibonacci(number - 1));

    return 1;
}

long fibonacci(long n)
{
    if (n <= 2)
        return 1;
    return (fibonacci(n - 1) + fibonacci(n - 2));
}