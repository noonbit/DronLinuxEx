#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Running ps with system() \n");

//	system("ps -ax");

	system("ps");
	printf("Done.\n");
	exit(5);
}
