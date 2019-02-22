//Lab 1A
//COSC130
//Lab synopsis
//Sai Thatigotla
//Date
//List any TAs/students that you worked with here.
#include <iostream>
#include <string>
using namespace std;

//Prototypes for the functions that you will write
int  CharToInt(char v){

	return v - '0';
}
char IntToChar(int v){

	return v + '0';
}
int StringToInt(string val){

	int num = 0;
	int counter = 0;
	int poweroften = 1; //will hold the base-10 value of the largest digit in number
	for(int i = val.length()-1; i >= 0; i--){ //iterates through string to find amount of digits/magnitude
			if(val[i]!='-'){
				for(int j = 0; j < counter; j++){ //starting from the ones place
					poweroften *= 10;
				}
				num += ((poweroften)*CharToInt(val[i]));
				counter++;
				poweroften = 1; //resetting value
			}
			else{
				num *= -1;
			}
		}
	return num;
}
string IntToString(int val){

	string s;
	int num = 0;
	int placeholder = 1;
	int countertwo = 0;
	if(val == 0){
		s = IntToChar(val);
		return s;
	}
	if(val < 0){ //adds negative sign to string if neg, and makes number posotive
		s += '-';
		val *= -1;
	}
	num = val;
	while(num != 0){ //counts digits
		num /= 10;
		countertwo++;
	}
	num = val;
	for(int j = 1; j < countertwo; j++){ //same as poweroften
		placeholder *= 10;
	}
	for(int i = countertwo; i > 0; i--)
	{
		s += IntToChar((val / placeholder)); //adds leftmost digit to string
		val -= (val / placeholder) * placeholder; //gets rid of leftmost digit
		placeholder /= 10;
	}
	return s;
}

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());
        return 0;
}
