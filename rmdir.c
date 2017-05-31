#include<stdio.h> 

int main(int argc, char* argv[])
{ 
int check;
char *dirname; 

dirname=argv[1];
check = rmdir(dirname); 

if (!check)
	printf("Directory deleted\n"); 
else 
{
	printf("Unable to remove directory\n");
	return 1; 
}
return 0; 
}

