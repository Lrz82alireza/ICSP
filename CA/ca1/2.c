#include <stdio.h>

int main(void)
{
    /*get days*/
    int day = 0;
    printf("enter number of days: ");
    scanf("%d", &day);

    /*get foods and sum cals*/
    int food = 0, sum_cal = 0;
    for (int i = 0; i < day; i++)
    {
        scanf("%d", &food);
        switch (food)
        {
        case 1:
            sum_cal += 329;
            break;
        case 2:
            sum_cal += 127;
            break;
        case 3:
            sum_cal += 61;
            break;
        case 4:
            sum_cal += 83;
            break;
        case 5:
            sum_cal += 156;
            break;
        case 6:
            sum_cal += 296;
            break;
        case 7:
            sum_cal += 496;
            break;
        case 8:
            sum_cal += 73;
            break;
        case 9:
            sum_cal += 34;
            break;
        case 10:
            sum_cal += 16;
            break;

        default:
            break;
        }
    }

    /*print body state*/
    if ((float)sum_cal / (day * 100) == 1)
    {
        printf("bedoon taghir");
    }
    else if ((float)sum_cal / (day * 100) > 1)
    {
        printf("chagh");
    }
    else if ((float)sum_cal / (day * 100) < 1)
    {
        printf("laghar");
    }
    return 0;
}