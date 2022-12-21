#include <stdio.h>

int main()
{
    int length, width, quit = 1, input = -1, x, m;
    char char1;

    while (quit)
    {
        printf("enter 1 for Multiplication table , 2 for triangle and 0 for stop program\n");
        scanf("%d", &input);
        scanf("%c", &char1);

        if (input < 0 || input > 2)
        {
            printf("invalid input\n");
        }
        else
        {
            switch (input)
            {
            case 1 :

                x = 1;
                printf("enter length and width like (5,3) [numbers shouldn't be less than 1]\n");

                while (x)
                {
                    scanf("%d,%d", &width, &length);
                    if (length < 1 || width < 1)
                    {
                        printf("numbers should be greater than 1\n");
                    }
                    else
                    {
                        x = 0;
                    }
                }

                for (int i = 1; i <= width; i++)
                {
                    for (int j = 1; j <= length; j++)
                    {
                       printf("%d ", i * j);
                    }
                    printf("\n");
                }
                break;
            
            case 2 :
                x = 1;

                printf("enter base of triangle) [it should be greater than 2 and odd]:\n");

                while (x)
                {
                    scanf("%d", &m);
                    if (m < 3 || m % 2 == 0)
                    {
                        printf("it should be greater than 2 and odd\n");
                    }
                    else
                    {
                        x = 0;
                    }
                }
                
    
                int Height = (m + 1) / 2;

                for (int i = 1; i <= Height; i++)
                {       
                    for (int k = 0; k < Height - i; k++)
                    {
                        printf("-");
                    }

                    for (int k = 1; k <= ((i - 1) * 2) + 1; k++)
                    {
                        printf("*");
                    }

                    for (int k = 0; k < Height - i; k++)
                    {
                        printf("-");
                    }
                    printf("\n");
                }
                break;

            case 0 :
                quit = 0;
                break;
            }
        }

    }
}
