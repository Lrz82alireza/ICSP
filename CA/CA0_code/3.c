#include <stdio.h>


// part 3
// The roots of the equation

float f(float x,float a, float b, float c)
{
	return x*x*x + a*x*x + b*x + c;
}
int main()
{
	float a, b, c;
	float err;
	// geting coefs
	scanf("%f %f %f", &a, &b, &c);
	// geting error
	scanf("%f", &err);
	float max = 0;
	
	
	// finding max coef
	if (a>b)
	{
		max = a;
	}
	else
	{
		max = b;
	}
	if (max<c)
	{
		max = c;
	}
	for (float i = -(max*max); i<max*max; i = i + err/1000)
	{
		// check error condition
		if (f(i,a,b,c) <= err/10 && f(i,a,b,c) >= -(err/10))
		{
			printf("%f", f(i,a,b,c));
			printf(" -------- ");
			printf("%f", i);
			printf("\n");
			i = i + 10 * err;
		}
	}
}