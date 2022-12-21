#include <stdio.h>
void prime(int number);

int main()
{
    /*get inputs*/
    int number;
    scanf("%d", &number);

    prime(number);

    return 1;
}

void prime(int number)
{
    int checker;
    int check[] = {2, 3, 5, 7};  // prime numbers < 10
    for (int i = 2; i < number; i++)
    {
        checker = 1;
        for (int j = 0; j < 4; j++)
        {
            if (i % check[j] == 0 && i != check[j])
            {
                checker = 0;
                break;
            }
        }
        if (checker)
        {
            printf("%d ", i);
        }
    }
}