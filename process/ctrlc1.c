#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//SIGINT handler

void sigHandler(int sig)
{
	static int cnt=0;

	switch(sig)
	{
		case SIGINT:
			printf("SIGINT received ...  %d\n", sig);
//			(void) signal(SIGINT, SIG_DFL);
//			signal(SIGINT, SIG_DFL);
			cnt++;
			if(cnt == 5) exit(0);
			break;

		case SIGQUIT:
			printf("SIGQUIT received ... %d\n", sig);
//			(void) signal(SIGQUIT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			break;
	}
}

void main()
{
	signal(SIGINT, sigHandler);
	signal(SIGQUIT, sigHandler);

	while(1)
	{
		printf("Hello World!\n");
		sleep(1);
	}
}
