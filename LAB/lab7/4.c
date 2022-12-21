#include <stdio.h>
#include <stdlib.h>
#define ZERO 0
void print_array(int * * array_of_int, int size1, int size2)
{
    for (int i = 0; i < size1; i++)
    {
        for (int j = 0; j < size2; j++)
            printf("%d ", array_of_int[i][j]);
        printf("\n");
    }
}
void initislizing_the_array(int * * array_of_int, int size1, int size2)
{
    for (int i = ZERO; i < size1; i++)
        for (int j = ZERO; j < size2; j++)
            array_of_int[i][j] = ZERO;
}
int main()
{
    int row, col, i;
    int **A;
    printf("Enter row and column:\n");
    scanf("%d %d", &row, &col);
    A = (int **)malloc(row * sizeof(int **)); /* 1. Complete this instruction */
    if (A == NULL)
        exit(EXIT_FAILURE);
    for (i = 0; i < row; i++)
    {
        A[i] = (int *)malloc(col * sizeof(int *)); /* 2. Complete this instruction */
        if (A[i] == NULL)
            exit(EXIT_FAILURE);
    }
    /* Now you have a 2D integer array */
    // Your Program Goes Here.
    initislizing_the_array(A, row, col);
    print_array(A, row, col);
    /* Don't forget to free the allocated memory when you don't need it any more */
    for (i = 0; i < row; i++)
        free(A[i]);
    free(A);
    return 0;
}