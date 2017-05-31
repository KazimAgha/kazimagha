#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
pid_t childpid = 0;
int a, b;
if (argc != 2){ /* check for valid number of command-line arguments */
fprintf(stderr, "Usage: %s processes\n", argv[0]);
return 1;
}
b = atoi(argv[1]);
for (a = 1; a < b; a++)
if (childpid = fork())
break;
fprintf(stderr, "a:%d process ID:%ld parent ID:%ld child ID:%ld\n",
a, (long)getpid(), (long)getppid(), (long)childpid);
return 0;
}

