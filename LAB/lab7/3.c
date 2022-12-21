#include <stdlib.h>
#include <stdio.h>
int main()
{
    getchar();
    int *p = NULL;
    int i = 500000;
    for (int j = 0; j < 3; j++)
    {
        p = realloc(p, i * sizeof(int)); /*put breakpoint here*/
        i += 500000;
    }
    free(p);
    getchar();
    return 0;
}