
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include "time.h"
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
void getTime(struct tm **time_f)
{
time_t sec;
time(&sec);
*time_f = localtime(&sec);
}
int main()
{
struct tm *time;
struct tm *new_time;
//getTime(&time);
int pid,status, fd[2],  buf[512];
pipe(fd);
pid=fork();
if(pid<0)printf("Ошибка создания процесса\n");
if(pid==0)
{	
	sleep(5);
	getTime (&time);
	close(fd[0]);
	write(fd[1], time, sizeof(struct tm));
	close(fd[1]);
	sleep(2);
	printf("Time: %d:%d:%d\n",time->tm_hour,time->tm_min, time->tm_sec);

	exit(0);
}
else{
	
	getTime(&new_time);
	close(fd[1]);
	read(fd[0],buf, sizeof(buf));
	close(fd[0]);
	wait(&status);
	printf("Time from pipe: %d:%d:%d\n",new_time->tm_hour, new_time->tm_min, new_time->tm_sec);
	
}
return 0;
}
