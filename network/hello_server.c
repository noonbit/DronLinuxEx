#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

// ./hello_server [PORT]

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
	char message[] = "Hello world!";
	char *ipaddr;

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
	write(clnt_sock, message, sizeof(message));
	
	// client info
	ipaddr = inet_ntoa(clnt_addr.sin_addr);
	printf("clint ip addr : %s\n", ipaddr);


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
		



	


		
	

