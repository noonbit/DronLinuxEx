#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	int ch;
	
	while((ch = getchar()) != EOF)
	{
		putchar(toupper(ch));
	}
	exit(0);
}
