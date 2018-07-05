#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int status;

	printf("Process ID = %d\n", getpid());
	printf("Parent Process ID = %d\n", getppid());

	pid = fork();
	if(pid < 0) 
	{
		printf("Error : fork() \n");
		return -1;
	}
	else if (pid == 0)
	{
		printf("Child : Hello ~~ \n");
		return 0;
	}
	else
	{
		printf("Parents : Hi !!\n");
		printf("Child PID : %d\n", pid);
	}

	pid = wait(&status);
	printf("EXIT:Child id = %d\n", pid);
	return 0;

}

