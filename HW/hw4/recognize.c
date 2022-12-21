#include <stdio.h>

void recognize(char s[], int sizeString)
{
    int counter = 0, check = 0;

    /*compare charecters*/
    for (int i = 0; i < sizeString; i++)
    {
        check = 1;
        for (int j = i + 1; j < sizeString; j++)
        {
            if (s[i] == s[j])
            {
                check = 0;
                break;
            }
        }
        if (check)
        {
            counter++;
        }
    }

    /*print output*/
    if (counter % 2 == 1)
    {
        printf("BLOCK THIS USER");
    }
    else
    {
        printf("CHAT WITH THIS USER");
    }
}