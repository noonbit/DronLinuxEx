#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void pr_exit(int status);

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
		raise(SIGINT);
//		return 0;
//		exit(11);
	}
	else
	{
		printf("Parents : Hi !!\n");
		printf("Child PID : %d\n", pid);
	}

	pid = wait(&status);
	printf("EXIT:Child id = %d\n", pid);

	pr_exit(status);
	return 0;

}

void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", \
			WTERMSIG(status), WCOREDUMP(status) ? "(core file generated)" : "");
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

