#include<stdio.h> 

int main(int argc, char* argv[])
{ 
int test;
char *drname; 

drname=argv[1];
test = rmdir(drname); 

if (!test)
	printf("Directory deleted\n"); 
else 
{
	printf("Unable to remove directory\n");
	return 1; 
}
return 0; 
}

