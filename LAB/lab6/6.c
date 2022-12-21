#include <string.h>
#include <stdio.h>

#define hight 4
#define width 3
void calc_transposed_matrix(int *first_matrix, int *second_matrix);

int main()
{
    int first_matrix[hight][width], second_matrix[width][hight], count = 1;
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < width; j++)
        {
            first_matrix[i][j] = j;
        }
    }
    // int *f = first_matrix;
    // int *s = second_matrix;
    calc_transposed_matrix (&first_matrix[0][0], &second_matrix[0][0]);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < hight; j++)
        {
            printf("%d", second_matrix[i][j]);
        }
        printf("\n");
    }
}

void calc_transposed_matrix(int *first_matrix, int *second_matrix)
{
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < width; j++)
        {
            *(second_matrix + i + (j * hight)) = *(first_matrix + j + (i * width));
        }
    }
}