#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>

#define BUFSIZE 256
#define FIFO_PERM (S_IRUSR | S_IWUSR)
#define FIFO_MODES O_RDONLY
#define FIFOARG 1
#define FIFO_PERMS (S_IRUSR | S_IWUSR)

int dofifoparent(const char *fifoname, const char *idstring);

ssize_t r_write(int fd, void *buf, size_t size);

int main(int argc, char *argv[])
{
	pid_t childpid;
	
	if(argc!=2){
		fprintf(stderr,"usage: %s pipename\n", argv[0]);
		return 1;	
	}

	if((childpid=fork())==-1){
		perror("failed to fork\n");	
		return 1;
	}

	if(childpid==0){	//child code

		return dofifoparent(argv[1],"this was written by fifoooooo\n");
	}
	else{ //parent code

	if ((mkfifo(argv[FIFOARG], FIFO_PERMS) == -1) && (errno != EEXIST)){
		if(errno != EEXIST){
			fprintf(stderr,"[%ld]: failed to create name pipe %s: %s\n", (long)getpid(),argv[1],strerror(errno));
			return 1;
		}
	}
		//return dofifoparent(argv[1],"this was written by parent\n");

	}

}//end main




int dofifoparent(const char *fifoname, const char *idstring) {
	char buf[BUFSIZE];
	int fd;
	int rval;
	ssize_t strsize;

	fprintf(stderr, "[%ld]:(parent) about to open FIFO %s...\n",(long)getpid(), fifoname);

	while (((fd = open(fifoname, O_WRONLY)) == -1) && (errno == EINTR)) 

		if (fd == -1) {
			fprintf(stderr, "[%ld]:failed to open named pipe %s for write: %s\n", (long)getpid(), fifoname, strerror(errno));
			return 1;
			}
	
		rval = snprintf(buf, BUFSIZE, "[%ld]:%s\n", (long)getpid(), idstring);

		if (rval < 0) {
			fprintf(stderr, "[%ld]:failed to make the string:\n", (long)getpid());
			return 1;
			}

		strsize = strlen(buf) + 1;
		fprintf(stderr, "[%ld]:about to write...\n", (long)getpid());
		rval = r_write(fd, buf, strsize);

		if (rval != strsize) {
			fprintf(stderr, "[%ld]:failed to write to pipe: %s\n", (long)getpid(), strerror(errno));
			return 1;
			}

		fprintf(stderr, "[%ld]:finishing...\n", (long)getpid());
		return 0;
}//end dofifoparent



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

