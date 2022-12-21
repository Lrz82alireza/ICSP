#include <stdio.h>

int main()
{
    int arr[4] = {1, 2, 3, 4};
    int *arr_cpy;
    arr_cpy = arr;
    printf("%p, %p", arr, arr_cpy);
    return 0;
    /*copy nist*/
}