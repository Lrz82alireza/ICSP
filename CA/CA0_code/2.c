#include <stdio.h>

#define daily_consumption 100
#define macaroni 329
#define ghorme 127
#define havij  61
#define carafs  83
#define sabzipolo  156
#define gardan  296
#define pache  496
#define kotlet  73
#define ash  34
#define salad  16


// part 2
// diet programm
int main()
{
	
	int number_of_days = 0;
	int base_energy = 0;
	//  get day numbers 
	scanf("%d", &number_of_days);
	if (number_of_days>0)
	{
		int food_type = 0;
		
		
		// get food list
		for (int i = 0; i < number_of_days; i++)
		{
			scanf("%d", &food_type);
			switch (food_type)
			{
			case 1:
				base_energy = base_energy + (macaroni - daily_consumption);
				break;
			case 2:
				base_energy = base_energy + (ghorme - daily_consumption);
				break;
			case 3:
				base_energy = base_energy + (havij - daily_consumption);
				break;
			case 4:
				base_energy = base_energy + (carafs - daily_consumption);
				break;
			case 5:
				base_energy = base_energy + (sabzipolo - daily_consumption);
				break;
			case 6:
				base_energy = base_energy + (gardan - daily_consumption);
				break;
			case 7:
				base_energy = base_energy + (pache - daily_consumption);
				break;
			case 8:
				base_energy = base_energy + (kotlet - daily_consumption);
				break;
			case 9:
				base_energy = base_energy + (ash - daily_consumption);
				break;
			case 10:
				base_energy = base_energy + (salad - daily_consumption);
				break;
			default:
				printf("input is invalid\n");
				break;
			}
			food_type = 0;
		}
		
		
		// show the result 
		if (base_energy>0)
		{
			printf("chagh\n");
		}
		else if (base_energy<0)
		{
			printf("laghar\n");
		}
		else if (base_energy==0)
		{
			printf("bedoon taghir\n");
		}
	}
	else
	{
		printf("input is invalid\n");
	}
}