#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <signal.h>
void func(int sockfd)
{
 char buff[80];
 int a;
 for (;;)
  {
    bzero(buff,sizeof(buff));
    printf("Client : ");
    a=0;
    while ((buff[a++]=getchar()) != '\n');
    write(sockfd,buff,sizeof(buff));
    bzero(buff,sizeof(buff));
    read(sockfd,buff,sizeof(buff));
    printf("From Server : %s",buff);
    if((strncmp(buff,"exit",4))==0)
    {
      printf("Client Exit...\n");
      printf("        WHATSAPP CHAT ROOM    ");
      break;
    }
   }
}

int main()
{
int sockfd,connfd;
struct sockaddr_in servaddr,client;
//socket create 
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd==-1)
{
printf("Creating Socket Failed");
exit(0);
}
else
printf("Creating Socket Was Successful\n");
bzero(&servaddr,sizeof(servaddr));

//assign IP, Port
printf("Please enter the server IP address:  ");
char ipserver[30];
scanf("%s",ipserver);
servaddr.sin_family=AF_INET;
servaddr.sin_port= htons(8888);
servaddr.sin_addr.s_addr=inet_addr (ipserver);
//connect
if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) <0)
{
printf("Connection with the server was failed...\n");
exit(0);
}
else
{
printf("You have connected to the server\n");
printf("Waiting for a response...\n\n If you want to quit, you have to press [ctrl+c]\n");
}
//functionf for chat
func(sockfd);
//close
close(sockfd);
}
