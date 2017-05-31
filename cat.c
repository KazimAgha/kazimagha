#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

main(int argc,char *argv[]){

printf("Name: Agha Ali Kazim \nRollno: DDP-FA14-BCS-146\nSection: C\n");

if(argc!=2){
printf("syntax error\n");
printf("syntax as felllows\n");
printf("command name file name\n");
exit(1);
}

int file1,count1;
char buff[22222];
file1=open(argv[1],O_RDONLY);

if(file1==-1){
	printf("file not exist\n");
	exit(1);
}
else{
while((count1=read(file1,buff,sizeof(buff)))>0){
	printf("%s",buff);
}
exit(0);
}
}
