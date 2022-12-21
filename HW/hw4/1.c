#include <stdio.h>
int main()
{
    int array[100], n, c, d, swap;
    printf("Enter number of elements\n");
    scanf("%d", &n);
    printf("Enter %d integers\n", n); // address -> value
    c = 0;                            // c meghdar avaliye nadarad
    while (c < n)                     // c <= n daraye yek khoone ezafi
    {
        scanf("%d", &array[c]);
        c++;
    }
    for (c = 0; c < n - 1; c++)
    {
        for (d = 0; d < n - c - 1; d++)
        {
            if (array[d] > array[d + 1])
            {
                swap = array[d]; // swap bayad aval neveshte shavad
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }
    printf("Sorted list in ascending order:\n");
    for (c = 0; c < n; c++) // c <= n daraye yek khoone ezafi
        printf("%d\n", array[c]);
    return 0;
}