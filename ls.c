#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
DIR *dp;
struct dirent *sd; 
struct stat mystat;
char buf[255];

printf("Name: Ahmed Ajmal\nRoll Number: DDP-FA14-BCS-151\nSection: C\n");

dp=opendir(argv[1]); 

while((sd=readdir(dp))!=NULL)
{
	printf("%s\t",sd->d_name);
}
printf("\n");
closedir(dp);
}
