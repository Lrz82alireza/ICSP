#include <stdio.h>

int g(int y)
{
    int j = 2;
    y = j * 3;
    return y;
}

int f(int x)
{
    return g(x);
}

int main()
{
    int a = 10;
    printf("%d", f(a));
    return 0;
}