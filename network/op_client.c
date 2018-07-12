#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "op.h"

#define BUFSIZE 50

void error_handling(char *message);

// ./hello_client [IP] [PORT]

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE]; 
	int str_len;
	int cnt, cnt1;
	char xxx;

	struct Op op;

	if(argc !=3)
	{
		printf("Usage : %s [IP] [port]\n", argv[0]);
		exit(1);
	}

//-----------------------------------------------------------
	printf("Operand Count : ");
	scanf("%d", &cnt1);
	op.cnt = (char)cnt1;

	for (cnt = 0; cnt <op.cnt; cnt++)
	{
		printf("Operand : ");
		scanf("%d", &op.op[cnt]);
	}

	printf("Operation : ");
	scanf("%c%c", &xxx, &op.oper);
//-----------------------------------------------------------

	// 1. socket() 
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	// 2. ip, port set
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	
	// 3. connect()
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");

	write(sock, (struct Op *)&op, sizeof(struct Op));

	close(sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
		



	


		
	
