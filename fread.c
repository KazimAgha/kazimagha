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

int dofifochild(const char *fifoname);

ssize_t r_read(int fd, void *buf, size_t size);

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

		//return dofifochild(argv[1]);
	}
	else{ //parent code

	if ((mkfifo(argv[FIFOARG], FIFO_PERMS) == -1) && (errno != EEXIST)){
		if(errno != EEXIST){
			fprintf(stderr,"[%ld]: failed to create name pipe %s: %s\n", (long)getpid(),argv[1],strerror(errno));
			return 1;
		}
	}
		//return dofifoparent(argv[1],"this was written by parent\n");
		return dofifochild(argv[1]);

	}

}//end main



int dofifochild(const char *fifoname){

	char buf[BUFSIZE];
	int fd;
	int rval;

	fprintf(stderr, "[%ld]:(child) about to open FIFO %s...\n", (long)getpid(), fifoname);

	while (((fd = open(fifoname, FIFO_MODES)) == -1) && (errno == EINTR));

		if (fd == -1) {
			fprintf(stderr, "[%ld]:failed to open named pipe %s for read: %s\n",(long)getpid(), fifoname, strerror(errno));
			return 1;
			}

		fprintf(stderr, "[%ld]:about to read...\n", (long)getpid());
		rval = r_read(fd, buf, BUFSIZE);

		if (rval == -1) {
			fprintf(stderr, "[%ld]:failed to read from pipe: %s\n",(long)getpid(), strerror(errno));
			return 1;
			}

		fprintf(stderr, "[%ld]:read %.*s\n", (long)getpid(), rval, buf);
		return 0;
}//end dofifochild


ssize_t r_read(int fd, void *buf, size_t size) {
ssize_t retval;
while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
return retval;
}//r_read

