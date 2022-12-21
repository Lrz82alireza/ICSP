#include <stdio.h>
int main()
{
    int i; /**/
    int z = 4;
    if (z - 4)
    {
        int i = 1;
        z = z + i;
    }
    else
    {
        int i = 1;
        z = i + 1;
        {
            int i = 1;
            z = i + 1;
        }
        z = i;
    }
    z = z + i;
    do
    {
        int i = 0;
        z = i + 1;
        i++;
    } while (i < 15);
    return 0;
}