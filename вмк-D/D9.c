#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <signal.h>
int main()
{
	pid_t pid;
	int fd[2];
	if(pipe(fd)==-1){perror("pipe");return 1;}

	pid = fork();
	if(pid< 0){perror("fork");return 2;}
	if(pid==0) 
	{
		int pid2=fork();
		if(pid2< 0){perror("fork");return 2;}
		if(pid2==0){
		  int num;
		  close(fd[0]);
		  while(scanf("%d",&num)==1)
			  write(fd[1],&num,sizeof(int));
		  close(fd[1]);
		}
		else{
        		wait(NULL);
				kill(getpid(),SIGKILL);
			}

	}
	else //dad
	{
		int num,sum=0;
		int max,min,count=0;
		close(fd[1]);
		while(read(fd[0],&num,sizeof(int))>0)
		{
		    if(count==0) {max=num;min=num;count++;}
		    if(num>max) max=num;
		    if(num<min) min=num;
		}
		printf("%d %d\n",min,max);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
}