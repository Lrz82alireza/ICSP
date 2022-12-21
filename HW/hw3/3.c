#include <stdio.h>
void schedule(int hour);

int main()
{
    int hour = 0;
    scanf("%d", &hour);

    schedule(hour);

    return 0;
}

void schedule(int hour)
{
    switch ((hour / 24) % 2)
    {
    case 0:
        if (hour % 24 < 12)
        {
            printf("A");
        }
        else
        {
            printf("B");
        }
        break;
    case 1:
        if (hour % 24 < 12)
        {
            printf("C");
        }
        else
        {
            printf("D");
        }
        break;
    }
}
