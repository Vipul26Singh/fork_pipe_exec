#include "header.h"


int main (int argc, char *argv[])
{
	FILE *fp = fopen("test.txt", "w");
	char string[100] = "";
	scanf("%s", string);
	fprintf(fp, "%s", string);
	strcat(string, "from child\n");
	printf("casca%s\n", string);
	fflush(stdout);
	sleep(1);

	return 0;

}
