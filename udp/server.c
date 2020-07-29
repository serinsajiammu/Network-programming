#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{

int i,j,k,n,socketid,nr1,nc1,nr2,nc2,A[10][10],B[10][10],C[10][10],rc[2][2];
struct sockaddr_in servaddr,cliaddr;
int len=sizeof(cliaddr);
//create socket
if((socketid=socket(AF_INET,SOCK_DGRAM,0))<0)
{
	printf("\nSocket creation failed");
	exit(0);
}

//address structure

bzero((char*)&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[1]));
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
 
//binding
 
if(bind(socketid,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
	printf("\nBinding failed");
	exit(0);
	}
 
//receiving size matrix

if((n=recvfrom(socketid,rc,sizeof(rc),0,(struct sockaddr*)&cliaddr,&len))==-1)
{
	printf("\nError in receiving size matrix");
	exit(0);


}

//receiving matrix A
if((n=recvfrom(socketid,A,sizeof(A),0,(struct sockaddr*)&cliaddr,&len))==-1)
{
	printf("\nError in receiving matrix A");
	exit(0);


}

//receiving matrix B
if((n=recvfrom(socketid,B,sizeof(B),0,(struct sockaddr*)&cliaddr,&len))==-1)
{
	printf("\nError in receiving matrix B");
	exit(0);


}

//multiplication

nr1=rc[0][0];
nc1=rc[0][1];
nr2=rc[1][0];
nc2=rc[1][1];

for(i=0;i<nr1;i++)
	for(j=0;j<nc2;j++)
		C[i][j]=0;


for(i=0;i<nr1;i++)
{
	for(j=0;j<nc2;j++)
	{
		for(k=0;k<nr2;k++)
			C[i][j]+=A[i][k]*B[k][j];
	}
}


//sending product matrix to client
n=sendto(socketid,C,sizeof(C),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
if(n<0)
{
	printf("\nError in sending sum matrix");
	exit(0);
}
//close(socketid);


}
