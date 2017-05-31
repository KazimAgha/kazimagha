#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){

printf("Name: Agha Ali Kazim\n Rollno: DDP-FA14-BCS-146\n Section: C\n");

char cwd[1024];
getcwd(cwd,sizeof(cwd));
printf("present  wrkng directory is %s\n",cwd);

}
