//Sai Thatigotla

#include <cstdio>
#include <iostream>

struct MyStruct 
{
	int result;
	int *opr_left;
	int *opr_right;
};

void Calculate(MyStruct &s, char op);

int main()
{
	int left;
	int right;
	char oper;

	printf("Enter left <op> right operands: ");
	scanf(" %d %c %d", &left, &oper, &right);  //taking in inputs

	MyStruct operation;

	operation.opr_left = &left;  //pointing left and right operators to left and right numbers
	operation.opr_right = &right;

	Calculate(operation, oper);

	printf("%d %c %d = %d\n", left, oper, right, operation.result);

}

void Calculate(MyStruct &s, char op)
{
		if(op == '+')
			{
				s.result = s.opr_left[0] + s.opr_right[0]; //dereferencing pointer members of struct
			}
		else if(op == '-')
			{
				s.result = s.opr_left[0] - s.opr_right[0];
			}
		else
			{
				s.result = -1;
			}
}
