#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct _num_st {
	int start;
	int end;
};

int main()
{
	struct timeval UTCtime_u_s, UTCtime_u_e, UTCtime_u_r ;
	int cnt, sum=0;

	struct _num_st st_num[2];
	st_num[0].start =     1;
	st_num[0].end   = 10000;

	st_num[1].start = 10001;
	st_num[1].end   = 20000;

gettimeofday(&UTCtime_u_s, NULL);

	for(cnt=st_num[0].start; cnt <= st_num[1].end; cnt++)
	{
		sum+=cnt;
	}


gettimeofday(&UTCtime_u_e, NULL);

	if(UTCtime_u_e.tv_usec >= UTCtime_u_s.tv_usec)
	{
		UTCtime_u_r.tv_usec = UTCtime_u_e.tv_usec - UTCtime_u_s.tv_usec;
		UTCtime_u_r.tv_sec  = UTCtime_u_e.tv_sec - UTCtime_u_s.tv_sec;
	}
	else
	{
		UTCtime_u_r.tv_usec = UTCtime_u_e.tv_usec - UTCtime_u_s.tv_usec + 100000;
		UTCtime_u_r.tv_sec  = UTCtime_u_e.tv_sec - UTCtime_u_s.tv_sec -1; 
	}	
	printf("time : %ld sec %ld usec \n", UTCtime_u_r.tv_sec, UTCtime_u_r.tv_usec);
	printf("sum = %d\n", sum);

	return 0;

}

