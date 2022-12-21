#include <stdio.h>
void sort(int *a, int *b, int *c);
int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    sort(&a, &b, &c);
    printf("%d < %d < %d", a, b, c);
    return 0;
}
void sort(int *a, int *b, int *c)
{
    int sorted[3] = {*a, *b, *c};
    int tmp;

    for (int j = 3; 0 < j; j--)
    {
        for (int i = 1; i < j; i++)
        {
            if (sorted[i] < sorted[i - 1])
            {
                tmp = sorted[i - 1];
                sorted[i - 1] = sorted[i];
                sorted[i] = tmp;
            }
        }
    }

    *a = sorted[0];
    *b = sorted[1];
    *c = sorted[2];
}