#include <stdlib.h>
#include <sys/stat.h> 
#include <stdio.h> 

int main(int argc, const char *argv[])
{

printf("Name: Ahmed Ajmal\nRoll Number: DDP-FA14-BCS-151\nSection: C\n");

if (mkdir(argv[1],0777) == -1) {
	perror(argv[0]);
	exit(EXIT_FAILURE);
}
return 0;
}
