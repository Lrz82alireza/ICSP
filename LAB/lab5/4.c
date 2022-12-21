#include <stdio.h>

int main()
{
    int number[10] = {2, 3, 6, 1, 4, 2, 6, 8, 9, 3}, temp[10], check = 0, sum = 0;

    for (int i = 0; i < 10; i++)
    {
        sum += number[i];
    }
    printf("%f\n", (float)sum / 10);
    for (int i = 0; i < 10; i++)
    {
        check = 1;
        for (int j = i; j >= 0; j--)
        {
            if (number[j] > number[i])
            {
                temp[i] = j;
                check = 0;
                break;
            }
        }
        if (check == 1)
        {
            temp[i] = -1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d, ", temp[i]);
    }
}