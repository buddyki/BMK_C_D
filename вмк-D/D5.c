#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
	int fd1,fd2,test=1;
	int tmp,dis1,dis2,dis,buf;
	struct stat s;

	if(argc<3) {
		fprintf(stderr,"Use:%s file1 file2\n",argv[0]);
		return 1;
	}

	fd1=open(argv[1],O_RDWR);
	if(fd1 == -1){
		fprintf(stderr,":Error:can't open file %s\n",argv[1]);
		return 2;
	}

	stat(argv[1],&s);
	fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,s.st_mode);
	if(fd2 == -1){
	    fprintf(stderr,"Error:can't open file %s\n",argv[2]);
		close(fd1);
		return 3;
	}
	 
      //tmp=buf[0];
	 if(read(fd1,&buf,sizeof(int))==sizeof(int)){
		tmp=buf;
	}
	else{
		close(fd1);close(fd2);
		return 0;
	}
    
while(test != 0){
	test=0;
	while(read(fd1,&buf,sizeof(int))==sizeof(int)){
		if(buf>tmp){
			lseek(fd1,-8,SEEK_CUR);
			write(fd1,&buf,sizeof(int));
			write(fd1,&tmp,sizeof(int));
			test=test+1;
		}	
		else{
			tmp=buf;
		}

	}
	lseek(fd1,0,SEEK_SET);
	if(read(fd1,&buf,sizeof(int))==sizeof(int)){
		tmp=buf;
	}
}

	lseek(fd1,0,SEEK_SET);
	while(read(fd1,&buf,sizeof(int))==sizeof(int)){		

    	write(fd2,&buf,sizeof(int));

	}
	close(fd1);
	close(fd2);
	return 0;
}

