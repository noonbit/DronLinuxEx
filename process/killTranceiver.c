#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int s, sig;
	int cnt;

	if(argc != 3 || strcmp(argv[1], "--help") == 0)
	{
		printf("Usage : %s pid sig-num\n", argv[0]);
		return 0;
	}

	sig = atoi(argv[2]);

	for (cnt = 0; cnt < 5; cnt++)
	{
		sleep(2);
		s = kill(atoi(argv[1]), sig);
		if(sig != 0)
		{
			if(s == -1) printf("Error : system call kill()\n");
			else if(s == 0) printf("Process exists and we can send it a signal\n");
		}
	}
	return 0;
}

