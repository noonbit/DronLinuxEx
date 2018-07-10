#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com-100.h"

int main()
{
	int running=1;
	void *shared_memory=(void *)0;
	char *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;
	int cnt;
	char qqq;

//	shmid=shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
//	shmid=shmget((key_t)0x100, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	shmid=shmget((key_t)0x100, 101, 0666 | IPC_CREAT);

	if(shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shared_memory=shmat(shmid, (void *)0, 0);
	if(shared_memory==(void *)-1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
//	printf("Memory attached at %X\n", (int)shared_memory);
	printf("Memory attached at %p\n", shared_memory);
	
	shared_stuff=(char *)shared_memory;
	printf("Memory attached at %p\n", shared_stuff);

	shared_stuff[100] = 0;		
	for(cnt = 0; cnt < 100; cnt++)
	{
		shared_stuff[cnt] = 100-cnt;	
	}

	printf("Enter 'q' ");
//wait while enter 'q'
	qqq = 'a';
	while(qqq != 'q')
	{
		scanf("%c", &qqq);
	}
	shared_stuff[100] = 1;	

	if(shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

