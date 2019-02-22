//lab3.cpp
//COSC130
//Sai Thatigotla
//9/14/18
#include <cstdio>
struct Real
{
     //sign bit
     int sign;
     //UNBIASED exponent
     long exponent;
     //Fraction including implied 1 at bit index 23
     unsigned long fraction;
};

Real Decode(int float_value);
int Encode(Real real_value);
Real Normalize(Real value);
Real Multiply(Real left, Real right);
Real Add(Real left, Real right);
long binAdd(long left, long right); //student made

int main(int argc, char *argv[])
{
     int left, right;
     char op;
     int value;
     Real rLeft, rRight, result;
     if (argc < 4) {
          printf("Usage: %s <left> <op> <right>\n", argv[0]);
          return -1;
     }
     sscanf(argv[1], "%f", (float *)&left);
     sscanf(argv[2], "%c", &op);
     sscanf(argv[3], "%f", (float *)&right);
     rLeft = Decode(left);
     rRight = Decode(right);

	// printf("Decode successful\n");

     if (op == 'x') {
          result = Multiply(rLeft, rRight);

	//	  printf("Multiply successful\n");
     }
     else if (op == '+') {
          result = Add(rLeft, rRight);
     }
     else {
          printf("Unknown operator '%c'\n", op);
          return -2;
     }
     value = Encode(result);
     printf("%.3f %c %.3f = %.3f (0x%08x)\n",
            *((float*)&left),
            op,
            *((float*)&right),
            *((float*)&value),
            value
            );
     return 0;
}
//Implement the following functions

Real Decode(int float_value)
{
	struct Real num;
	if(((float_value >> 31) & 1) == 1){
		num.sign = 1;
	}else{
		num.sign = 0;
	}
	
	for(int i = 30; i >22; i--){
		if((float_value >> i) & 1){					//checks if bit is a one
			num.exponent = num.exponent | 1 << (i - 23); //adds 1 bit
			}
	}

	//printf("num.exponenet before: %ld\n",num.exponent);

	num.exponent -= 127;

	//printf("num.exponenet after bias: %ld\n", num.exponent);

	for(int i = 21; i >=0; i--){		//skips implied one
		if((float_value >> i) & 1){
		num.fraction = num.fraction | (1 << i);  //combines one if bit is one
		}
	}

	num.fraction = num.fraction | (1 << 23);

	return num;
	
}
int Encode(Real real_value)
{
	int numE = 0;
	if(real_value.sign == 1){
		numE = numE | (1 << 31);
	}
		
	int tmpexp = real_value.exponent + 127;
	
	for(int i = 7; i >= 0; i--){		//gets exponent ands adds it to respective part in IEEE 754
		if((tmpexp >> i) & 1){
			numE = numE | (1 << (i + 23));
		}
	}
	
	for(int i = 22; i >=0; i--){
		if((real_value.fraction >> i) & 1){
			numE = numE | (1 << i);
		}
	}
		return numE;
}
Real Normalize(Real value)
{
	struct Real numN;
	numN.sign = value.sign;
	numN.fraction = 0;
	bool hit = false;  //indicates when to start keeping track of offset

	int counter = 0;
	for(int i = 31; i > 22; i--){
		if((value.fraction >> i) & 1){
			hit = true;
		}
		if(hit){
			counter++; //how much the bits need to be shifted
		}
	}
	numN.exponent = counter;

	for(int i = counter + 21; i >= counter; i--){
		numN.fraction = numN.fraction | (((value.fraction >> i) & 1)<< (i-counter));
	}

	numN.fraction = numN.fraction | (1 << 22);  //implied one
	return numN;

}
Real Multiply(Real left, Real right)
{
	//printf("Inside Multiply function\n");

	struct Real numM;
	
	/*if(left.sign == 1){
		if(right.sign == 1){
			numM.sign = 0;
		}
		else{
			numM.sign = 1;
			}
		}
	else{
			if(right.sign == 1){
				numM.sign = 1;
			}
			else{
				//printf("Both 0 - posotive\n");
				numM.sign = 0;
		}
	}*/

	numM.sign = left.sign^right.sign;

	//printf("Multiply sign successful\n");

	numM.exponent = binAdd((long)left.exponent,(long)right.exponent);

	//printf("exponent successful: %ld \n", numM.exponent);

	//int shifter = 0;  //shifts botton row
	//int placeholder = 0;		//palceholder value for successive rows; how much extra to shift by	
	
	int counter = 0;

	long tmp = 0;
	long ftemp = 0;
		for(int i = 0; i < 64; i++){
			//tmp = tmp | ((((left.fraction << i) & (((right.fraction >> shifter) & 1)<<i))>>i)<<(shifter + placeholder));
			//shifter++;
			if(counter == 0)
			{
				ftemp = (left.fraction << i) & (right.fraction >> i);
				counter++;
			}
			else if(counter == 1)
			{
				tmp = (left.fraction << i) & (right.fraction >> i);
				tmp = binAdd(ftemp, tmp);
				counter = 0;
			}
		}

	return numM;
}

long binAdd(long left, long right){
	int carry = 0;
	long sum = 0;
	int tmpL = 0;
	int tmpR = 0;

	for(int i = 0; i < 64; i++){
		tmpL = (left >> i) & 1;
		tmpR = (right >> i) & 1;

		if(carry == 1){
			//if((carry | tmpL) & (~carry | ~tmpL)){
			  if(carry ^ tmpL){ //checking for 1 + 0
				tmpL = 1;
				carry = 0;
			}
			else{			//if top bit is also a one and carry, make it 10 and keep the carry
				tmpL = 0;
			}
		}

		//if((tmpL | tmpR) & (~tmpL | ~tmpR)){ 
		  if(tmpL ^ tmpR){	//if xor is 1
			sum = sum | (1 << i);
		}
		else if(tmpL == 1 && tmpR == 1){
				carry = 1;
		}
	}
	return sum;
}

Real Add(Real left, Real right)
{
	struct Real numA;
	long lnum = (long)left.fraction;
	long rnum = (long)right.fraction;
	lnum = lnum ^ (1 << 23);
	rnum = rnum ^ (1 << 23);

	lnum = lnum << left.exponent;
	rnum = rnum << right.exponent;

	if(left.sign == 1 || right.sign == 1){
		if(left.sign == 1 && right.sign == 0){
		numA.fraction = (int)(binAdd(((~(binAdd(binAdd(~lnum, 1), rnum)))),1));  //two's complement, then adding, then adding again
			if(left.exponent > right.exponent){
				numA.sign = 1;
				}
			else if(right.exponent > left.exponent){
				numA.sign = 0;
				}
			else if(right.exponent == left.exponent){
				if(right.fraction > left.fraction)
				{
					numA.sign = 0;
				}
				else if(left.fraction > right.fraction){
					numA.sign = 1;
				}
				else {
					numA.sign = 0;
				}
			}
		}else
		{
			numA.fraction = (int)binAdd(~(binAdd(binAdd(~rnum, 1), lnum)),1);
			if(left.exponent > right.exponent){
				numA.sign = 0;
				}
			else if(right.exponent > left.exponent){
				numA.sign = 1;
				}
			else if(right.exponent == left.exponent){
				if(right.fraction > left.fraction)
				{
					numA.sign = 1;
				}
				else if(left.fraction > right.fraction){
					numA.sign = 0;
				}
				else {
					numA.sign = 0;
				}
			}
			}
			}else
			{
				numA.fraction = (int)(~binAdd(lnum, rnum));
				numA.sign = 0;
			}
		
	return Normalize(numA);	
}
