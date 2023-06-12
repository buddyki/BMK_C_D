#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

#define BUF_SIZE 256

int main(int argc,char *argv[])
{
	int fd1,fd2,size;
	char buf[BUF_SIZE];
	struct stat s;

	if(argc<3){
		//fprintf(stderr,"Use:%s file1 file2\n",argv[0]);
		return 1;
	}
	fd1=open(argv[1],O_RDONLY);
	if(fd1 == -1)
	{
		//fprintf(stderr,":Error:can't open file %s\n",argv[1]);
		return 1;
	}
	stat(argv[1],&s);
	fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,s.st_mode);
	if(fd2 == -1)
	{
		//fprintf(stderr,"Error:can't open file %s\n",argv[2]);
		close(fd1);
		return 1;
	}

	char ch;
	int count=0,a;
	char arr[BUF_SIZE];
	while((size = read(fd1,buf,1))>0){
		ch=*buf;
		//printf("ch=%c ",ch);

		if( (ch>='a' && ch <= 'z')||(ch>='A' && ch<='Z') )
		{
			//printf("ch1=%c ",ch);
			count=count+1;
			if(count<10) a=1;
			else if(count <100 ) a=2;
			else if(count <1000 ) a=3;
			else a=4;
			//*arr=count+'0';
			sprintf(arr,"%d",count);
			write(fd2,buf,1);
		}
		else
		{
			if(count != 0) write(fd2,arr,a);
			write(fd2,buf,1);		
			count=0;

		}

	}
	if(count != 0) write(fd2,arr,a);

	close(fd1);
	close(fd2);
	return 0;

}