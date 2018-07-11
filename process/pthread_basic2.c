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

void *t_function(void *data)
{

	int cnt, sum=0;
	struct _num_st *id;

	id = (struct _num_st *)data;

//	printf("id->start = %d, id->end = %d\n", id->start, id->end);

	for(cnt=id->start; cnt <= id->end; cnt++)
	{
		sum+=cnt;
	}
	
	return (void *)(sum);
}

int main()
{
	struct timeval UTCtime_u_s, UTCtime_u_e, UTCtime_u_r ;

	struct _num_st st_num[2];

	pthread_t p_thread[2];
	int err;
	int status[2];
	int a = 1;
	int b = 2;

	st_num[0].start =     1;
	st_num[0].end   = 10000;

	st_num[1].start = 10001;
	st_num[1].end   = 20000;

gettimeofday(&UTCtime_u_s, NULL);

	if((err = pthread_create(&p_thread[0], NULL, t_function, (void *)&st_num[0]))<0)
	{
		perror("thread create error : ");
		exit(1);
	}
	if((err = pthread_create(&p_thread[1], NULL, t_function, (void *)&st_num[1])) < 0)
	{
		perror("thread create erro : ");
		exit(2);
	}

	pthread_join(p_thread[0], (void **)&status[0]);
	pthread_join(p_thread[1], (void **)&status[1]);

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
	printf("sum1 = %d\n", status[0]);
	printf("sum2 = %d\n", status[1]);
	printf("sum1 + sum 2 = %d\n", status[0]+status[1]);

	return 0;


}

