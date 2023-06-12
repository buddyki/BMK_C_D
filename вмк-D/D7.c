#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
int main()
{
	int n;
	scanf("%d",&n);

	int fd[2];
	if(pipe(fd)== -1){perror("pipe");return 1;}

	int id= fork();
	if(id< 0){perror("fork");return 2;}
	if(id==0) //son
	{
		close(fd[1]); //读取
		int pid;                //dad id
		if(read(fd[0],&pid,sizeof(int)) == -1){perror("read");return 2;}
		close(fd[0]);

		for(int i=0;i<n;i++){  //sson fork
			//printf("getpid=%d getppid=%d id=%d\n",getpid(),getppid(),pid);
			fprintf(stdout,"%d %d\n", getpid()- getppid(), getpid()-pid );
			int id2=fork();
			//printf("id2 = %d\n", id2);
			if(id2<0){perror("fork");return 2;}
			if(id2==0){
        		fprintf(stderr,"PID=%d PPID=%d\n",getpid(),getppid());
				fflush(stdout);
			}
			else{
        		wait(NULL);
				kill(getpid(),SIGKILL);
			}
		}
	}

	else  //dad
	{
		close(fd[0]);  //写入
		int pid=getpid();
        //printf("dad pid = %d\n", pid);
		if(write(fd[1],&pid,sizeof(int))==-1){perror("write");return 2;}

		close(fd[1]);
		wait(NULL);
	}
	return 0;
}
