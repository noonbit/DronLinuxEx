#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//SIGINT handler

void sigHandler(int sig)
{
	static int cnt=0;

	printf("killTest : i got signal %d, cnt = %d\n",sig, cnt+1);
	cnt++;
	if(cnt == 5) exit(0);
}

void main()
{
	signal(SIGINT, sigHandler);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
