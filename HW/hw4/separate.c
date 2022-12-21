#include <stdio.h>

void separate(int arr[], int sizeArr)
{
    int odd[sizeArr], even[sizeArr], size_even = 0, size_odd = 0, swap; // size of even and odd numbers

    /*make odd and even array*/
    for (int i = 0; i < sizeArr; i++)
    {
        if (arr[i] % 2 == 0)
        {
            even[size_even] = arr[i];
            size_even++;
        }
        else
        {
            odd[size_odd] = arr[i];
            size_odd++;
        }
    }

    /*sort odd numbers*/
    for (int i = 0; i < size_even - 1; i++)
    {
        for (int j = 0; j < size_even - i - 1; j++)
        {
            if (even[j] > even[j + 1])
            {
                /*swap*/
                swap = even[j];
                even[j] = even[j + 1];
                even[j + 1] = swap;
            }
        }
    }

    /*sort odd numbers*/
    for (int i = 0; i < size_odd - 1; i++)
    {
        for (int j = 0; j < size_odd - i - 1; j++)
        {
            if (odd[j] > odd[j + 1])
            {
                /*swap*/
                swap = odd[j];
                odd[j] = odd[j + 1];
                odd[j + 1] = swap;
            }
        }
    }

    /*print sorted even numbers*/
    for (int i = 0; i < size_even; i++)
    {
        printf("%d", even[i]);
        if (i < size_even - 1)
        {
            printf(",");
        }
    }
    printf("\n");

    /*print sorted odd numbers*/
    for (int i = 0; i < size_odd; i++)
    {
        printf("%d", odd[i]);
        if (i < size_odd - 1)
        {
            printf(",");
        }
    }
}