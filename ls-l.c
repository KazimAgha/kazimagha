#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
int main(int argc,char **argv)
{
DIR *dp;
struct dirent *dirp;

if ((dp = opendir(argv[1])) == NULL)


printf("can’t open %s", argv[1]);

while ((dirp=readdir(dp)) != NULL){

struct stat fileStat;

stat(dirp->d_name,&fileStat);
printf(dirp->d_name);

printf("—————————\n");

printf("FileSize:\t\t%dbytes\n",fileStat.st_size);
printf("NumberofLinks:\t%d\n",fileStat.st_nlink);
printf("File inode:\t\t%d\n",fileStat.st_ino);}
return 0;
}
