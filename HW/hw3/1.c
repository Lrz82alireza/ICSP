#include <stdio.h>
#include <math.h>
void equation(int a, int b, int c);

int main()
{
    /*get inputs*/
    double a, b, c;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    equation(a, b, c);
    return 0;
}

void equation(int a, int b, int c)
{
    /*make delta*/
    double delta = (b * b - 4 * a * c);

    if (delta > 0)
    {
        printf("%lf , ", ((-b + sqrt(delta)) / (2 * a)));
        printf("%lf", ((-b - sqrt(delta)) / (2 * a)));
    }
    else if (delta == 0)
    {
        printf("%lf", (-b / (2 * a)));
    }
    else
    {
        printf("NO ROOT FOUND");
    }
}