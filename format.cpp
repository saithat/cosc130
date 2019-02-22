#include <cstdio>
#include <cstdlib>
#include <cstring>
int main(int argc, char **argv){
	char *s;
	char * name;
	int hex;
	FILE *fout;

	fout = stdout;

	

	name = strdup("addi");
	hex = 0x12345678;

	s = strdup("x2, x2, -64");

	fprintf(fout, "     %-6s%-19s// 0x%08x\n", name, s, hex);


	return 0;
}
