#include <stdio.h>
#include <stdlib.h>

int main()
{
    int seed = 810101532;
    int input;
    int x = 1;

    srand(seed);
    int random_number = rand() % 100;

    while (x)
    {
        scanf("%d", &input);
        if (input > random_number)
        {
            printf("try less than it\n");
        }
        else if (input < random_number)
        {
            printf("try greater than it\n");
        }
        else
        {
            printf("congratulations!! you just wast your time and it won't BACK :)\n");
            x = 0;
        }
    }
}