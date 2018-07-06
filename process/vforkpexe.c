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

	pid = vfork();

	switch(pid)
	{
		case -1:
			printf("Error : fork() \n");
			return -1;
		case 0: 		
			execlp("./pexec", "./pexec", NULL);
			return -1;
		default:
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

