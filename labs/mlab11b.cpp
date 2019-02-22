//Sai Thatigotla
#include <stdio.h>
#include <string>
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Incorrect arguements!\n");
	}
	unsigned long long hex;
	sscanf(argv[1], " %llx", &hex);
	
	unsigned long long ppn2 = (hex >> 28) & 67108863;
	unsigned long long ppn1 = (hex >> 19) & 511; 
	unsigned long long ppn0 = (hex >> 10) & 511; 

	unsigned long long result = 0;

	result = result | (ppn2 << 30);
	result = result | (ppn1 << 21);
	result = result | (ppn0 << 12);
	printf(" Page Table Entry: 0x%016llx \n Physical Address: 0x%016llx \nEntry Bits: \n", hex, result);

	if((hex & 1) == 1)
	{
		printf("\tBit V: SET\n");
	}
	else
	{
		printf("\tBit V: ClEAR\n");

	}
	if(((hex >> 1) & 1) == 1)
	{
		printf("\tBit R: SET\n");

	}
	else
	{
		printf("\tBit R: ClEAR\n");

	}
	if(((hex >> 2) & 1) == 1)
	{
		printf("\tBit W: SET\n");

	}
	else
	{
		printf("\tBit W: ClEAR\n");

	}
	if(((hex >> 3) & 1) == 1)
	{
		printf("\tBit X: SET\n");

	}
	else
	{
		printf("\tBit X: ClEAR\n");

	}
	if(((hex >> 4) & 1) == 1)
	{
		printf("\tBit U: SET\n");

	}
	else
	{
		printf("\tBit U: ClEAR\n");

	}
	if(((hex >> 5) & 1) == 1)
	{
		printf("\tBit G: SET\n");

	}
	else
	{
		printf("\tBit G: ClEAR\n");

	}
	if(((hex >> 6) & 1) == 1)

	{
		printf("\tBit A: SET\n");

	}
	else
	{
		printf("\tBit A: ClEAR\n");

	}
	if(((hex >> 7) & 1) == 1)
	{
		printf("\tBit D: SET\n");

	}
	else
	{
		printf("\tBit D: ClEAR\n");

	}

	return 0;
}
