#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
//#include "restart.h"
#define FIFOARG 1

ssize_t r_write(int fd, void *buf, size_t size) {
char *bufp;
size_t bytestowrite;
ssize_t byteswritten;
size_t totalbytes;
for (bufp = buf, bytestowrite = size, totalbytes = 0;
bytestowrite > 0;
bufp += byteswritten, bytestowrite -= byteswritten) {
byteswritten = write(fd, bufp, bytestowrite);
if ((byteswritten) == -1 && (errno != EINTR))
return -1;
if (byteswritten == -1)
byteswritten = 0;
totalbytes += byteswritten;
}
return totalbytes;
}//r_write

ssize_t r_read(int fd, void *buf, size_t size) {
ssize_t retval;
while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
return retval;
}//r_read

int copyfile(int fromfd, int tofd) {
char buf[1024];
int bytesread, byteswritten;
int totalbytes = 0;
for ( ; ; ) {
if ((bytesread = r_read(fromfd, buf, 1024)) <= 0)
break;
if ((byteswritten = r_write(tofd, buf, bytesread)) == -1)
break;
totalbytes += byteswritten;
}
return totalbytes;
}

int main (int argc, char *argv[]) {
int requestfd;
if (argc != 2) {
/* name of server fifo is passed on the command line */
fprintf(stderr, "Usage: %s fifoname > logfile\n", argv[0]);
return 1;
}
/* open a read/write communication endpoint to the pipe */
if ((requestfd = open(argv[FIFOARG], O_RDWR)) == -1) {
perror("Server failed to open its FIFO");
return 1;
}
copyfile(requestfd, STDOUT_FILENO);
return 1;
}

