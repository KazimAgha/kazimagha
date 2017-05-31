#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFOARG 1
#define FIFO_PERMS (S_IRUSR | S_IWUSR)

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

int main (int argc, char *argv[]) {

time_t curtime;
int len;
char requestbuf[PIPE_BUF];
int requestfd;
if (argc != 2) { /* name of server fifo is passed on the command line */
fprintf(stderr, "Usage: %s fifoname", argv[0]);
return 1;
}/* create a named pipe to handle incoming requests */
if ((mkfifo(argv[FIFOARG], FIFO_PERMS) == -1) && (errno != EEXIST)) {
perror("Server failed to create a FIFO");
return 1;
}
if ((requestfd = open(argv[FIFOARG], O_WRONLY)) == -1) {
perror("Client failed to open log fifo for writing");
return 1;
}
curtime = time(NULL);
snprintf(requestbuf, PIPE_BUF, " %s",ctime(&curtime));
len = strlen(requestbuf);
if (r_write(requestfd, requestbuf, len) != len) {
perror("Client failed to write");
return 1;
}
//r_close(requestfd);
return 0;
}

