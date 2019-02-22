#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct PERSON 
{
	  char name[51];
      int age;
	  char gender;
};
extern "C" 
{
	PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
	//char Search(PERSON people[], int num_people, const char* name, int age, char gender);
	int Median(const int array[], int array_size, int *buffer);
}
int main()
{
	PERSON p[4];
	//char str1[] = "abcdefghijklmnopqrstuvwxyz0123456789.!.!.!.!.!.!.";
	char str0[] = "Dave";
	strcpy(p[0].name, str0);
	
	char str1[] = "John";
	strcpy(p[1].name, str1);

	char str2[] = "Will";
	strcpy(p[2].name, str2);

	char str3[] = "Ozymandias";
	strcpy(p[3].name, str3);

	p[0].age = 31;
	p[1].age = 25;
	p[2].age = 6;
	p[3].age = 3000;

	p[0].gender = 'M';
	p[1].gender = 'M';
	p[2].gender = 'F';
	p[3].gender = 'K';

	//const char* testname = "Dave";

	//printf("%x\n", &p[1]);
	if(Search(p, 4, str3, 2000, 'K')!= nullptr)
	{
		printf("Name: %s\n", (Search(p, 4, str3, 2000, 'K'))->name);
	}
	else if(Search(p, 4 ,str3, 2000, 'k') == nullptr)
	{
		printf("Fail\n");
	}
	else
	{
		printf("loop failed\n");
	}

	//printf("last char read: %d\n", Search(p, 4, str0, 31, 'M'));

	
	int buffer[7];
	const int arr[7] = {2, 7, 5, 3, 7, 0, 4};
	printf("Median: %d\n", Median(arr, 7, buffer));
	printf("Unsorted array:\n\t");
	for(int i = 0; i < 7; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\nsorted array:\n\t");
	for(int i = 0; i < 7; i++)
	{
		printf("%d ", buffer[i]);
	}
	printf("\n");
	return 0;

}
