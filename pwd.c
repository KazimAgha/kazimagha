#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){

printf("Name: Ahmed Ajmal\nRoll Number: DDP-FA14-BCS-151\nSection: C\n");

char cwd[1024];
getcwd(cwd,sizeof(cwd));
printf("present  working directory is %s\n",cwd);

}
