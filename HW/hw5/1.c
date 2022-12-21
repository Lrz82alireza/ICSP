int main()
{
    int *a[5]; // same as: int *(a[5]);
    int(*b)[5];

    printf("*a[5] vs (*b)[5] : %d vs %d", sizeof (a), sizeof(b));
    // *a[5] vs (*b)[5] : 20 vs 4
}   