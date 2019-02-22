//Sai Thatigotla
//9/28/18
//TAs:Grace
#include <cstdio>
int main(int argc, char** argv)
{

	FILE *f;
	char dkey;
	int nkey;
	char buf;
	char *array;
	int index;
	int size = 0;
	
	if(argc !=4)
	{
		printf("Invaid number of arguments");
	}
	f = fopen(argv[1],"rb");  //opens file

	if(f == nullptr)
	{
		printf("Invalid file");
		return -1;
	}

	sscanf(argv[2], "%c", &dkey); //reads dkey
	sscanf(argv[3], "%d", &nkey); //reads nkey

	fseek(f,0,SEEK_END);

	size = (ftell(f))/8;
	array = new char[size]; //array to hold the decrypted string

	fseek(f,0,SEEK_SET);
	

	for(int i = 0;i < size; i++)
	{
		fread(&buf,1,sizeof(buf),f); //reads encrypted data block
		fseek(f,3,SEEK_CUR); //skips padding
		fread(&index,1,sizeof(index),f); //reads encrypted index block
		index = index^nkey;
		if(index < 0 || index > size)  //checking if index is out of bounds with the amount of blocks in file
		{
			printf("Error decoding chunk %d, decoded index was %d, but max chunk is %d\n", i, index, size);
			return 0;
		}
		array[index] = buf^dkey;
	}

	printf("\n%s\n",array);


	fclose(f);

	return 0;
}
