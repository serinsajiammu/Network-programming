#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char *argv[])
{

struct sockaddr_in server, cli;
int cli_len,socketid,n,i,len,data,temp;

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
server.sin_port=htons(atoi(argv[1]));
server.sin_addr.s_addr=htons(INADDR_ANY);

//binding

if ((bind(socketid, (struct sockaddr*)&server, sizeof(server))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
else
        printf("Socket successfully binded..\n"); 

//listening

if ((listen(socketid, 5)) != 0) { 
	printf("Listen failed...\n"); 
	exit(0); 
	} 
else
	printf("Server listening..\n"); 

//accepting

if((data=accept(socketid,(struct sockaddr*)&cli,&cli_len))<0)
	{
	printf("server accept failed\n");
	exit(0);
	}
else
	printf("server accept the client\n");
		 
//communication process
	
int ch;
for(ch==1;ch<5;ch++)
{
read(data,buffer,sizeof(buffer));

printf("\nMessage from client:%s\n",buffer);

printf("\nEnter message to client:");
fgets(buffer,sizeof(buffer),stdin);
//buffer[strlen(buffer)-1]='\0';

write(data,buffer,sizeof(buffer));

printf("\nDo you want to continue communication?(0/1)");
scanf("%d",&ch);
}
	

exit(0);
close(data);
close(socketid);




}
