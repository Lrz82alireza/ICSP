
int fact(int n)
{
    if (n == 0)
    {
        return 1;
    }

    int output = 1;
    for (int i = 1; i <= n; i++)
    {
        output *= i;
    }
    return output;
}