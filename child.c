#include "header.h"


int main (int argc, char *argv[])
{
	int processId = atoi(argv[1]);

	//char filename[30];
	
	//sprintf(filename, "chile_test_%d.txt", processId);
	
	//FILE *fp = fopen(filename, "w");
	char string[100] = "";
	scanf("%s", string);
//	fprintf(fp, "read:%s", string);
	strcat(string, "from child\n");
	printf("%s\n", string);
	fflush(stdout);

	return 0;

}
