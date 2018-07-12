#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "op.h"

void error_handling(char *message);

// ./hello_server [PORT]

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	int str_len, cnt, result = 0;
	struct Op op;
	int counter;

	if(argc !=2)
	{
		printf("Usage : %s [port]\n", argv[0]);
		exit(1);
	}
	// 1. socket() 
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	// 2. ip, port set
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	// 3. bind()
	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	// 4. listen()
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	// 5. accept()
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("acept() error");

	str_len = read(clnt_sock, &op, sizeof(struct Op));
	if(str_len == -1)
		error_handling("read() error");
//--------------------------------------------------	
	counter = (int) op.cnt;
	if(op.oper == '+')
	{
		result = 0;
		for (cnt = 0; cnt < counter ; cnt++)
		{
			result += op.op[cnt];
			printf("%d",op.op[cnt]);
			if(cnt < counter-1) printf(" + ");
			else printf(" = ");
		}
		printf("%d \n", result);
	}
	else if(op.oper == '-') 
	{
		result = op.op[0];
		printf("%d",op.op[0]);
		for (cnt = 0; cnt < counter-1 ; cnt++)
		{
			result = result - op.op[cnt+1];
			printf(" - ");
			printf("%d",op.op[cnt+1]);
		}
		printf(" = %d \n", result);
	}
	else if(op.oper == '*') 
	{
		result = 1;
		for (cnt = 0; cnt < counter ; cnt++)
		{
			result *= op.op[cnt];
			printf("%d",op.op[cnt]);
			if(cnt < counter-1) printf(" * ");
			else printf(" = ");
		}
		printf("%d \n", result);
	}
//--------------------------------------------------

	close(clnt_sock);
	close(serv_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
		



	


		
	

