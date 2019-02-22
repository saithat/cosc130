//Sai Thatigotla
// 9/7/18
// COSC 130
// Asked for help from TA:Grace
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BITSET {
	public:
		BITSET();
		bool Test(int n);	
		void Set(int loc);
		void Clear(int loc);
		int GetSet(int num);
		int GetNumSets();
	private:
		vector<int> bitset;
};

BITSET::BITSET(){
	bitset.resize(1);
	bitset[0] = 0;
}

bool BITSET::Test(int loc){
	return ((bitset[loc/32]) & (1 << (loc % 32))); //testing bit with a logical "and" by left shifting a 1 by the location of bit
}

void BITSET::Set(int loc){
	if(((long unsigned int)(loc/32)+1) > bitset.size()){ //the long unsigned type cast is because it complained that I was comparing an int to long unsigned
		bitset.resize((loc/32)+1);  //the +1 in the line above was because bitset.size() is not zero indexed
	}
	bitset[loc/32] = (bitset[loc/32] | (1 << (loc % 32)));
}

void BITSET::Clear(int loc){
	bitset[loc/32] = ~((~bitset[loc/32]) | (1 << (loc % 32))); //logical "or" an inverted set and then invert the set again
	int counter = 0;
	int numsets = 0;
	int set = bitset.size()-1;
	while((set > 0) && (counter == numsets)){  //when counter != numsets that means it read a set that wasn't zero, so it stops keeping track of sets to clear
	numsets++;
		if(bitset[set] == 0){
			counter++;
		}
		set--;
	}
	bitset.resize(bitset.size()-counter);
}

int BITSET::GetNumSets(){
	return bitset.size();
}
int BITSET::GetSet(int num){
	return bitset[num];
}

string ToBinary(int val, int space){
	string bin;
	int num = val;
	int counter = 0;
	for(int i = 31; i >= 0; i--){
		if((num >> i) & 1){  //right shifts the num to isolate the bits from left to right
			bin += "1";
		}
		else{
			bin += "0";
		}
		counter++;
		if((counter == space) && (i!=0)){ //makes surve to keep even spacing and not add space after bit 0
			bin += " ";
			counter = 0;
		}
	}
	return bin;
}

int main(){
	BITSET b;
	char command;
	int index;
		printf("\nEnter a command and index: ");
		scanf(" %c", &command);
		while(command!='q'){
		switch(command){
			case 't':
				{
				scanf(" %d", &index);
				if(b.Test(index)){
					printf("True");
				}
				else{
					printf("False");
				}
				break;
				}
			case 's':
				{
			scanf(" %d", &index);
					b.Set(index);
					break;
				}
			case 'c':
				{
			scanf(" %d", &index);
					b.Clear(index);
					break;
				}
			case 'g':
				{
			scanf(" %d", &index);
					if(index <= b.GetNumSets() && (index > 0)){
						printf((ToBinary(b.GetSet(index-1),3)).c_str());
					}
					else{
						printf("Sorry that set doesn't exist!");
					}
					break;
				}
			case 'n':
				{
					printf("\n%d", b.GetNumSets());
					break;
				}
			case 'q':
				{
					return 0;
				}
			default:
				{
					printf("\nTry again!");
					break;
				}
	}
		printf("\nEnter a command and index: ");
		scanf(" %c", &command);

	}
	
return 0;
}
