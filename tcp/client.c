#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/socket.h>


int main(int argc, char *argv[])
{

struct sockaddr_in server;
int socketid;
char buffer[100];

//socket creation

socketid = socket(AF_INET, SOCK_STREAM, 0); 
if (socketid == -1) { 
	printf("Socket creation failed...\n"); 
	exit(0); 
    } 
else
        printf("Socket successfully created..\n"); 
        
        
//address structure initialisation

bzero(&server, sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[2]));
inet_pton(AF_INET,argv[1],&server.sin_addr);

//connection

if (connect(socketid, (struct sockaddr*)&server, sizeof(server)) != 0) { 
	printf("Connection with the server failed...\n"); 
	exit(0); 
	    } 
else
	printf("Connected to the server..\n"); 
		
//communication process

int ch;
for(ch=1;ch<5;ch++)
{     
printf("Enter message:");
	  
fgets(buffer,sizeof(buffer),stdin);

write(socketid,buffer,sizeof(buffer));


read(socketid,buffer,sizeof(buffer));

printf("\nMessage from server:%s\n",buffer);

printf("\nEnter do you want to continue communication?(0/1)");
scanf("%d",&ch);
}
exit(0);
close(socketid);


}
