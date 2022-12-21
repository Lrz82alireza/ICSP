#include <stdio.h>

int main()
{
    /*x^3 + ax^2 + bx + c*/
    /*|a| = A*/
    int a, b, c, A, B, C;
    float error = 0;

    /*get inputs*/
    printf("enter inputs: ");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    scanf("%f", &error);

    /*getting the absolute value*/
    if (a > 0)
    {
        A = a;
    }
    else
    {
        A = -a;
    }

    if (b > 0)
    {
        B = b;
    }
    else
    {
        B = -b;
    }

    if (c > 0)
    {
        C = c;
    }
    else
    {
        C = -c;
    }

    /*finding the most factor*/
    int most_f; // most factor
    if (A > B)
    {
        if (A > C)
        {
            most_f = A;
        }
        else // A <= C
        {
            most_f = C;
        }
    }
    else // A <= B
    {
        if (B > C)
        {
            most_f = B;
        }
        else // B <= C
        {
            most_f = C;
        }
    }

    /*finding The roots of the equation*/
    int check_sign = -1;
    int counter = 3;
    for (float i = -(float)(most_f * most_f); i <= (most_f * most_f); i += error)
    {
        switch (check_sign)
        {
        case 1:
            if (((i * i * i) + (a * i * i) + (b * i) + c) <= 0)
            {
                printf("%.4f\n", i);
                counter--;
                check_sign = -1;
            }
            break;

        case -1:
            if (((i * i * i) + (a * i * i) + (b * i) + c) >= 0)
            {
                printf("%.4f\n", i);
                counter--;
                check_sign = 1;
            }
            break;
        }
    }

    /*if equation didnt have 3 roots*/
    for (int i = 0; i < counter; i++)
    {
        printf("bedoon rishe\n");
    }

    return 0;
}