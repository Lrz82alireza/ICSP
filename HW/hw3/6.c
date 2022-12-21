#include <stdio.h>

void calendar(int *year, int *month, int *day);

int main()
{
    int year = 1300, month = 1, day; // nday = number of days ; Pday = plus days
    /*get days*/
    scanf("%d", &day);

    calendar(&year, &month, &day);
    
    printf("%d.%d.%d", year, month, day + 1);
}

void calendar(int *year, int *month, int *day)
{
    /*check for years*/
    while (365 <= *day)
    {
        *year += 1;
        *day -= 365;
    }

    int counter = 1;
    while (*day >= 30)
    {
        if (*day >= 31 && counter <= 6)
        {
            counter++;
            *month += 1;
            *day -= 31;
        }
        else if (*day >= 30 && counter <= 11)
        {
            counter++;
            *month += 1;
            *day -= 30;
        }
        else
        {
            break;
        }
    }
}