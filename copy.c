#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
	int count, fd_in, fd_out;
	char buf[BUFSIZE];

	if(argc < 3)
	{
//		printf("Usage : copy file1 file2 \n");
//		fflush(stdout);
		write(1, "Usage : copy file1 file2 \n", 27);
		return -1;
	}
	if((fd_in = open(argv[1], O_RDONLY)) < 0)
	{
		perror(argv[1]);
		return -1;
	}
	if((fd_out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR)) < 0)
	{
		perror(argv[2]);
		return -1;
	}

	while((count = read(fd_in, buf, sizeof(buf))) > 0)
		write(fd_out, buf, count);

	close(fd_in);
	close(fd_out);
	return 0;

}
