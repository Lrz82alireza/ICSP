#include <stdio.h>
#define SIZE 5

int main()
{
    int i, j;
    int table[SIZE][SIZE] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {1, 2, 3, 4, 5}, {4, 6, 7, 3, 2}};
    int second_table[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            second_table[j][i] = table[i][j];
        }
    } // transposing

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            table[i][j] = second_table[i][j];
        }
    } // replacing

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            printf("%d ", table[i][j]);
        printf("\n");
    } // printing the result
    return 0;
}
