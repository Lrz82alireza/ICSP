#include <stdio.h>
#define SIZE 4

int main ()
{
    int i, sum = 0, num[SIZE];
    printf("Enter %d number:\n", SIZE);
    for (i = 0; i < SIZE; i++)
        scanf("%d", (num + i));
    for (i = 0; i < SIZE; i++)
        sum += *(num + i);
    printf("Sum: %d\n", sum);
    return 0;
}