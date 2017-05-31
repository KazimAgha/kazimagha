#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
 
#define buf_Size 1024

int main(int argc, char *argv[]){

printf("Name: Agha Ali Kazim\n Roll NU: DDP-FA14-BCS-146\n Section: C\n");

char *buf[buf_Size];
int fd1,fd2,readfb,writef;

if(argc!=3){
printf("incomplete arguments\n");
exit(1);
}

fd1=open(argv[1],O_RDONLY);

if(fd1==-1){
	printf("ERROR SOURCE FIlE\n");
	exit(1);
}

fd2=open(argv[2],O_WRONLY);
	
if(fd2==-1){
	printf("ERROR SOURCE FILE\n");
	exit(1);
}

while((readfb=read(fd1,buf,buf_Size)) >0){
	if(write (fd2,buf,readfb)!=readfb){
		printf("ERROR IN WRITING\n");
	}
}

if(readfb==-1){
	printf("ERROR IN READING\n");
}

if(close(fd1)==-1){
	printf("Error in cloosing file\n");
}

if(close(fd2)==-1){
	printf("Error in cloosing file\n");
}

exit(0);

}
