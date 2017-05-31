 
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#define PRINT_HIDDEN 0
int main(int argc,char *argv[])
{

//printf("Talha fayyaz Reg no : ddp-fa14-bcs-091 Section:A\n");
DIR *dp;
struct dirent *sd; 


dp=opendir(argv[1]); 
//char c=argv[1];
while((sd=readdir(dp))!=NULL)
{
//switch(c){
//case 'a':
///printf("hi");

if(PRINT_HIDDEN)
{
if(sd->d_name[0]!='.'){
printf("%s\t",sd->d_name);
 }
}
else{
if(sd->d_name[0]!='.')
{printf("%s\t",sd->d_name);
}
}

}
printf("\n");
closedir(dp);
}
