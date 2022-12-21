#include <stdio.h>
void calendar(int *day);

int main()
{
    int year = 1300, month = 1, day; // nday = number of days ; Pday = plus days
    /*get days*/
    scanf("%d", &day);

    calendar(&day);

    printf("%d\n", year);
    printf("%d\n", month);
    printf("%d\n", day);
}

void calendar(int *day)
{  
    *day += 1;
}