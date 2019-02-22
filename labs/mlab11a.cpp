//Sai Thatigotla
#include <stdio.h>
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Incorrect arguements!\n");
	}
	unsigned long long hex;
	sscanf(argv[1], " %llx", &hex);
	
	int vpn2 = (hex >> 30) & 511;
	int vpn1 = (hex >> 21) & 511; //0000 0000 0001 1111 1111
	int vpn0 = (hex >> 12) & 511; //000000000000000 0001 1111 1111
	int poff = hex & 4095;

	printf("Address: 0x%016llx \nVPN[2] = %d \nVPN[1] = %d \nVPN[0] = %d \nPOFF = %x (%d) \n",hex, vpn2, vpn1, vpn0, poff, poff);

	return 0;
}
