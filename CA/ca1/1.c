#include <stdio.h>
#define max_room 16

int main(void)
{
    /*get inputs*/
    int number = 0;
    float hight = 0;
    printf("enter number:");
    scanf("%d", &number);
    printf("enter hight:");
    scanf("%f", &hight);

    /*separate floor and room from input*/
    int floor = (number - number % 100) / 100;
    int room = number % 100;

    /*check inputs*/
    if (floor == 0 || room > max_room || number < 0)
    {
        printf("number invalid");
        return 1;
    }
    else if (hight == 0 || hight > 1)
    {
        printf("hight invalid");
        return 1;
    }

    /*print area*/
    for (int i = 4, count = 1; i <= max_room; i += 4, count++)
    {
        if (i - 3 <= room && room <= i)
        {
            printf("%d\n", count);
            break;
        }
    }

    /*print number of jumps*/
    int jcount = 1;
    while (jcount * (hight / 2) + hight < (floor * 2) + 1)
    {
        jcount++;
    }
    printf("%d", jcount);

    return 0;
}