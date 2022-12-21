#include <stdio.h>

// part1 
// find region and jump
int main()
{
	int room_number;
	float first_jump_height;
	// geting room number
	scanf("%d", &room_number);
	// geting first jump height
	scanf("%f", &first_jump_height);
	int region = 0;
	int Number_of_jumps=0;
	region = room_number % 100;
	//finding region of jumping
	if (region <= 4 && region>=1)
	{
		region = 1;
	}
	else if (region <= 8 && region >= 5)
	{
		region = 2;
	}
	else if (region <= 12 && region >= 9)
	{
		region = 3;
	}
	else if (region <= 16 && region >= 13)
	{
		region = 4;
	}
	else
	{
		region = 0;
	}
	// finding the number of jumps
	float height = ((room_number - (room_number % 100)) / 50) - first_jump_height;
	while (height >= -1)
	{
		height = height - (first_jump_height / 2);
		Number_of_jumps++;
	}

	if (region>0 && Number_of_jumps>0 && room_number <= 816 && first_jump_height<=1)
	{
		printf("the region of jumping is : region %d \n", region);
		printf("Number of required jumps is  : %d \n", Number_of_jumps);
	}
	else
	{
		printf("the input is invalid\n");
	}

}