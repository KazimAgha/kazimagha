#include<stdio.h>//printf
#include<string.h>//strlen
#include<sys/socket.h>//socket
#include<arpa/inet.h>//inet_addr
int main(int argc,char *argv[])
{
if(argc!=3){
printf("error");
exit(1);
}
int sock,a;
struct sockaddr_in server;
char message[1000],server_reply[2000];

//Create socket
sock=socket(AF_INET,SOCK_STREAM,0);
if(sock==-1)
{
printf("Could not create socket");
}
puts("Socket created");
server.sin_addr.s_addr=inet_addr(argv[1]);
server.sin_family=AF_INET;
server.sin_port=htons(8888);
//Connect to <span id="k2085f6x0y_9" class="k2085f6x0y">remote server</span>
if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
{
perror("connect failed. Error");
return 1;
}
puts("Connected\n");

//keep communicating with server
//Send some data
if(send(sock,argv[2],strlen(argv[2]),0)<0)
{
puts("Send failed");
return 1;
}
//Receive a reply from the server
if(recv(sock,server_reply,2000,0)<0)
{puts("recv failed");

}
puts("Server reply :");
puts(server_reply);

close(sock);
return 0;
}
