#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	time_t UTCtime;
	struct tm *tm;
	char buf[BUFSIZ];
	struct timeval UTCtime_u;

	// 1. time()
	time(&UTCtime);
	printf("time : %u\n", (unsigned)UTCtime);	
		
	tm = localtime(&UTCtime);
	printf("asctime : %s\n", asctime(tm));

	strftime(buf, sizeof(buf), "%Y-%m-%e %H:%M:%S %A", tm);
	printf("strftime : %s\n", buf);
	

	// 2. gettimeofday() micro sec
	gettimeofday(&UTCtime_u, NULL);
	printf("gettimeofday : %ld / %ld \n", UTCtime_u.tv_sec, UTCtime_u.tv_usec);	

	// 3. 

	return 0;
}
