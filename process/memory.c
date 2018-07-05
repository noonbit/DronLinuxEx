#include <stdio.h>
#include <stdlib.h>

#define mem_size 200

int a = 10;
int b = 0;
int array[10];
int const img[5] = {0,1,2,3,4};
char *pData="Hello World";

void main(void)
{
	static int c;
	static int d=15;
	char label[100];
	char *pLabel;

	printf(" 1. %p \n", pData);

	pData = malloc(sizeof(char)*mem_size);
	printf(" 2. %p \n", pData);
	free(pData);

//	pLabel = malloc(sizeof(char)*mem_size);
//	free(pLabel);

	printf(" 3. %p \n", &a);
	printf(" 4. %p \n", &b);
	printf(" 5. %p \n", array);
	printf("10. %p \n", &c);
}

