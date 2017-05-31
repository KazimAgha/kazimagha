#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

main(int argc,char *argv[]){

printf("Name: Ahmed Ajmal\nRoll Number: DDP-FA14-BCS-151\nSection: C\n");

if(argc!=2){
printf("syntax error\n");
printf("syntax should be as felllows\n");
printf("command name file name\n");
exit(1);
}

int file,count;
char buff[22222];
file=open(argv[1],O_RDONLY);

if(file==-1){
	printf("file do not exist\n");
	exit(1);
}
else{
while((count=read(file,buff,sizeof(buff)))>0){
	printf("%s",buff);
}
exit(0);
}
}
