#include <stdio.h>

int main()
{
    int x;
    int *ptr;
    int **ptr2;
    int **ptr3;
    /*مقدار موجود در اشارهگرها و متغیر فوق را توجیه کنید */
    x = 25;
    ptr = &x;
    ptr2 = &ptr;
    /*اکنون مقادیر دو اشاره گر فوق نشان دهنده چه هستند؟*/
    *ptr = 2 * **ptr2;
    printf("x = %d and address of x = 0x%p = 0x%p = 0x%x = 0x%p \n",
           x, ptr, &x, &x, *ptr2);
    /* مقدار خروجی را مشاهده کنید. */
    return 0;
}
