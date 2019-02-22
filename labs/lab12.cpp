//Sai Thatigotla
#include <cstdio>
#include <string>
using namespace std;
class Decode
{
		public:
		bool bin; //whether user wants in abi or xreg format
		const char* const abireg[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
		//abireg is indexed based on value of reg, e.g zero:x0:index 0
		string type_A(int inst);  //imm[31:12] rd 0110111
		string type_jal(int inst); //imm[20|10:1|11|19:12]
		string type_B(int inst); //imm[11:0] rs1 000(or whatever the 3 bit is) rd 0000011(also 1100111)
		string type_B2(int inst); //like B except it prints in reg, reg, reg/imm format
		string type_C(int inst); //imm[11:5] rs2 rs1 000(etc.) imm[4:0] 0100011
		string type_D(int inst); //0000000(or 0100000) rs2 rs1 000(etc.) rd 0110011
		string type_sd(int inst); //imm[11:5] rs2 rs1 011 imm[4:0] 0100011
		string type_E(int inst); //000000 shamt rs1 001(etc.) rd 0010011
		string type_F(int inst); //0000000 shamt rs1 001(etc.) rd 0011011
		string type_jalr(int inst); //imm[11:0] rs1 000 rd 1100111
};
int main(int argc, char **argv)
{
	if(argc < 3 || argc > 4)
	{
		printf("Incorrect inputs!");
		return 1;
	}

	FILE *input;

	input = fopen(argv[1], "rb");

	if(input == nullptr)
	{
		printf("Invalid File\n");
		return -1;
	}

	FILE *output;

	if(argv[2][0] == '-')
	{
		output = stdout;
	}
	else
	{
		output = fopen(argv[2], "wt");
	}

	bool ABI = true;

	if(argc == 4){
		if(argv[3][0] == 'x'){
		ABI = false;
		}
	}

	fseek(input, 0, SEEK_END);

	int size = ftell(input)/4;

	fseek(input, 0, SEEK_SET);

	int * instruct;
	instruct = new int[size];

	for(int i = 0; i < size; i++)
	{
		fread(&instruct[i], 1, 4, input);
	}

	fseek(input, 0, SEEK_SET);

	Decode me;
	me.bin = ABI;
	
	int tmp;

	for(int i=0; i < size; i++)
	{
		switch (instruct[i] & 0x0000007f) //gets the last 7 bits
		{
			case 0b0110111:
				fprintf(output, "     %-6s%-19s// 0x%08x\n", "lui", me.type_A(instruct[i]).c_str(), instruct[i]);
				break;
			case 0b1101111:
				fprintf(output, "     %-6s%-19s// 0x%08x\n", "jal", me.type_jal(instruct[i]).c_str(), instruct[i]);
				break;
			case 0b1100111:
				fprintf(output, "     %-6s%-19s// 0x%08x\n", "jalr", me.type_jalr(instruct[i]).c_str(), instruct[i]);
				break;
			case 0b0000011:
				tmp = (instruct[i] >> 12) & 7;
				if(tmp == 0) //tmp is the 3 bit value in most instructions left of the last 7 bits
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "lb", me.type_B(instruct[i]).c_str(), instruct[i]);
				} else if(tmp == 1)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "lh", me.type_B(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 2)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "lw", me.type_B(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 6)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "lwu", me.type_B(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 3)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "ld", me.type_B(instruct[i]).c_str(), instruct[i]);
				}
				break;
			case 0b0010011:
				tmp = (instruct[i] >> 12) & 7;
				if(tmp == 0)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "addi", me.type_B2(instruct[i]).c_str(), instruct[i]);
				} else if(tmp == 4)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "xori", me.type_B2(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 6)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "ori", me.type_B2(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 7)
				{
					fprintf(output,"     %-6s%-19s// 0x%08x\n", "andi", me.type_B2(instruct[i]).c_str(), instruct[i]);
				}
				else if(tmp == 1)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "slli", me.type_E(instruct[i]).c_str(), instruct[i]);
				} else if(tmp == 5)
				{
					if(((instruct[i] >> 30) & 1) == 0)
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "srli", me.type_E(instruct[i]).c_str(), instruct[i]);
					}else
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "srai", me.type_E(instruct[i]).c_str(), instruct[i]);
					}
				}
				break;
			case 0b0100011:
				tmp = (instruct[i] >> 12) & 7;
				if(tmp == 0)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sb", me.type_C(instruct[i]).c_str(), instruct[i]);
				} else if(tmp == 1)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sh", me.type_C(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 2)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sw", me.type_C(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 3)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sd", me.type_sd(instruct[i]).c_str(), instruct[i]);
				}
				break;
			case 0b0110011:
				tmp = (instruct[i] >> 12) & 7;
				if(tmp == 0)
				{
					if(((instruct[i] >> 30) & 1) == 1)
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sub", me.type_D(instruct[i]).c_str(), instruct[i]);

					}else
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "add", me.type_D(instruct[i]).c_str(), instruct[i]);
					}
				} else if(tmp == 1)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sll", me.type_D(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 4)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "xor", me.type_D(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 5)
				{
					if(((instruct[i] >> 30) & 1) == 1)
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sra", me.type_D(instruct[i]).c_str(), instruct[i]);
					}else
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "srl", me.type_D(instruct[i]).c_str(), instruct[i]);
					}
				}else if(tmp == 6)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "or", me.type_D(instruct[i]).c_str(), instruct[i]);
				}else if(tmp == 7)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "and", me.type_D(instruct[i]).c_str(), instruct[i]);
				}
				break;
			case 0b0011011:
				tmp = (instruct[i] >> 12) & 7;
				if(tmp == 1)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "slliw", me.type_F(instruct[i]).c_str(), instruct[i]);
				} else if(tmp == 5)
				{
					if(((instruct[i] >> 30) & 1) == 1)
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "sraiw", me.type_F(instruct[i]).c_str(), instruct[i]);
					}else
					{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "srliw", me.type_F(instruct[i]).c_str(), instruct[i]);
					}
				}else if(tmp == 0)
				{
					fprintf(output, "     %-6s%-19s// 0x%08x\n", "addiw", me.type_B2(instruct[i]).c_str(), instruct[i]);
				}
				break;
			default:
				fprintf(output, "     %-6s%-19s// 0x%08x\n", "inv", "invalid", instruct[i]);
				break;
		}
	}
	fclose(input);

	return 0;
}
string Decode::type_A(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f; //isolates the last 7
	int imm = (inst >> 12) & 1048575; //isolates the immediate
	imm = imm << 12;
	if(bin)
	{
		sprintf(buf, "%s, %d", abireg[rd], imm);
	}
	else
	{
		sprintf(buf, "x%d, %d", rd, imm);
	}

	return buf;
}
string Decode::type_jal(int inst)
{
	char buf[50]; //for storing new string
	int rd = (inst >> 7) & 0x1f;

	int imm = (((inst >> 12) & 0xff) << 12);
	imm = imm | (((inst >> 20) & 1) << 11); //11
	imm = imm | (((inst >> 21) & 0x3ff) << 1); //10:1
	imm = imm | ((inst >> 31) & 1) << 20; //20
	imm = (imm << 12) >> 12; //to preserve the sign bit if it's negative

	if(bin)
	{
		sprintf(buf, "%s, %d", abireg[rd], imm);
	}
	else
	{
		sprintf(buf, "x%d, %d", rd, imm);
	}

	return buf;
}
string Decode::type_B(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;

	bool negative = false;
	if(((inst >> 31) & 1) == 1) //two's complement
	{
		negative = true;
		inst = (~(inst >> 20) + 1)<< 20;
	}

	int imm = (inst >> 20) & 0xfff;
	if(negative)
	{
		imm = (~imm)+1;
	}

	if(bin)
	{
		sprintf(buf, "%s, %d(%s)", abireg[rd], imm, abireg[rs1]);
	}
	else
	{
		sprintf(buf, "x%d, %d(x%d)", rd, imm, rs1);
	}

	return buf;
}
string Decode::type_B2(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;

	bool negative = false;
	if(((inst >> 31) & 1) == 1)
	{
		negative = true;
		inst = (~(inst >> 20) + 1)<< 20;
	}

	int imm = (inst >> 20) & 0xfff;
	if(negative)
	{
		imm = (~imm)+1;
	}

	if(bin)
	{
		sprintf(buf, "%s, %s, %d", abireg[rd], abireg[rs1], imm);
	}
	else
	{
		sprintf(buf, "x%d, x%d, %d", rd, rs1, imm);
	}

	return buf;
}
string Decode::type_C(int inst)
{
	char buf[50];
	int rs1 = (inst >> 15) & 0x1f;
	int rs2 = (inst >> 20) &0x1f;

	int imm = (inst >> 7) & 0x1f;
	imm = imm | (((inst >> 25) & 0x7f) << 5);

	if(bin)
	{
		sprintf(buf, "%s, %d(%s)", abireg[rs2], imm, abireg[rs1]);
	}
	else
	{
		sprintf(buf, "x%d, %d(x%d)", rs2, imm, rs1);
	}

	return buf;
}
string Decode::type_D(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;
	int rs2 = (inst >> 20) &0x1f;

	if(bin)
	{
		sprintf(buf, "%s, %s, %s", abireg[rd], abireg[rs1], abireg[rs2]);
	}
	else
	{
		sprintf(buf, "x%d, x%d, x%d", rd, rs1, rs2);

	}

	return buf;
}
string Decode::type_E(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;

	bool negative = false;
	if(((inst >> 31) & 1) == 1)
	{
		negative = true;
		inst = (~(inst >> 20) + 1)<< 20;
	}

	int shamt = (inst >> 20) & 0x3f;
	if(negative)
	{
		shamt = (~shamt)+1;
	}

	if(bin)
	{
		sprintf(buf, "%s, %s, %d", abireg[rd], abireg[rs1], shamt);
	}
	else
	{
		sprintf(buf, "x%d, x%d, %d", rd, rs1, shamt);
	}

	return buf;
}
string Decode::type_F(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;

	bool negative = false;
	if(((inst >> 31) & 1) == 1)
	{
		negative = true;
		inst = (~(inst >> 20) + 1)<< 20;
	}

	int shamt = (inst >> 20) & 0x1f;
	if(negative)
	{
		shamt = (~shamt)+1;
	}

	if(bin)
	{
		sprintf(buf, "%s, %s, %d", abireg[rd], abireg[rs1], shamt);
	}
	else
	{
		sprintf(buf, "x%d, x%d, %d", rd, rs1, shamt);
	}

	return buf;
}
string Decode::type_sd(int inst)
{
	char buf[50];
	int rs1 = (inst >> 15) & 0x1f;
	int rs2 = (inst >> 20) &0x1f;

	int imm = (inst >> 7) & 0x1f;
	imm = imm | (((inst >> 25) & 0x7f) << 5);

	if(bin)
	{
		sprintf(buf, "%s, %d(%s)", abireg[rs2], imm,  abireg[rs1]);
	}
	else
	{
		sprintf(buf, "x%d, %d(x%d)", rs2, imm, rs1);

	}

	return buf;
}
string Decode::type_jalr(int inst)
{
	char buf[50];
	int rd = (inst >> 7) & 0x1f;
	int rs1 = (inst >> 15) &0x1f;

	bool negative = false;
	if(((inst >> 31) & 1) == 1)
	{
		negative = true;
		inst = (~(inst >> 20) + 1)<< 20;
	}

	int imm = (inst >> 20) & 0xfff;
	if(negative)
	{
		imm = (~imm)+1;
	}

	if(bin)
	{
		sprintf(buf, "%s, %s, %d", abireg[rd], abireg[rs1], imm);
	}
	else
	{
		sprintf(buf, "x%d, x%d, %d", rd, rs1, imm);

	}

	return buf;
}

