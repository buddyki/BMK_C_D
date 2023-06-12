#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	long fd;
	long max,distance,buf;

	if(argc<2) {
		fprintf(stderr,"Use command %s input.bin",argv[0]);
		return 1;
	}

	fd=open(argv[1],O_RDWR);
	if(fd == -1){
		fprintf(stderr,"Can't open file");
		return 2;
	}

	
	 if(read(fd,&buf,sizeof(long))){
		max=buf;
		distance=0;
	}
	else return 0;

	while(read(fd,&buf,sizeof(long))){
		if(buf>max){
			max=buf;
			distance=lseek(fd,0,SEEK_CUR)-sizeof(long);
			//printf("D1=%ld",disdance);
			//distance=ftell(&buf);
			//printf("D2=%ld",distance);
		}
	}
	lseek(fd,distance,SEEK_SET);
	max=max*2;
	write(fd,&max,sizeof(long));
	
	close(fd);
	return 0;
}
	  