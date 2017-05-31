#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
int main(int argc, char **argv) { 
int a, fd[2]; 
pid_t pid; 
char line[64]; 
if (pipe(fd) < 0) { 
perror("pipe error"); 
exit(1); 
} 
if ((pid = fork()) < 0) { 
perror("fork error"); 
exit(1); 
} else if (pid > 0) { /* parent process start */ 
close(fd[0]); 
printf("P=> Parent process pid %d and its ppid %d.\n", 
getpid(), getppid()); 
printf("P=> Sending a message to child process pid %d:\n", pid); 
snprintf(line, 64, "Hello child! I'm your parent pid %d!\n", 
getpid()); 
write(fd[1], line, strlen(line)); 
close(fd[1]); 
} else { /* child process start*/ 
close(fd[1]); 
printf("C=> Child process pid %d and its ppid %d.\n", 
getpid(), getppid()); 
printf("C=> Reading  message from parent pid %d:\n", getppid()); 
a = read(fd[0], line, 64); 
close(fd[1]); 
write(STDOUT_FILENO, line, a); 
} 
exit(0); 
} 

