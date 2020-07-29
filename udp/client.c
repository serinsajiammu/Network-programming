#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
int i,j,n,socketid,A[10][10],B[10][10],C[10][10],rc[2][2],r1,c1,r2,c2;

struct sockaddr_in servaddr;

printf("\nEnter rows and columns of first matrix(A):");
scanf("%d%d",&r1,&c1);
printf("\nEnter rows and columns of second matrix(B):");
scanf("%d%d",&r2,&c2);

if(c1!=r2)
	{
	printf("\nCannot perform matrix multiplication");
	exit(0);
	}
rc[0][0]=r1;
rc[0][1]=c1;
rc[1][0]=r2;
rc[1][1]=c2;

printf("\nEnter elements of Matrix A:");
for(i=0;i<r1;i++)
	for(j=0;j<c1;j++)
		scanf("%d",&A[i][j]);
		

printf("\nEnter elements of Matrix B:");
for(i=0;i<r2;i++)
	for(j=0;j<c2;j++)
		scanf("%d",&B[i][j]);
		

printf("\nMatrix A:\n");
for(i=0;i<r1;i++)
	{
	for(j=0;j<c1;j++)
		printf("%d\t",A[i][j]);
		
	printf("\n");
	}

printf("\nMatrix B:\n");
for(i=0;i<r1;i++)
	{
	for(j=0;j<c1;j++)
		printf("%d\t",B[i][j]);
		
	printf("\n");
	}

//socket creation


if ( (socketid = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
	printf("Socket creation failed"); 
	exit(0); 
    } 

//address structure initialisation

bzero((char*)&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(atoi(argv[2]));
inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

//sending rc matrix

n=sendto(socketid,rc,sizeof(rc),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(n<0)
{
	printf("\nError in sending size matrix");
	exit(0);
}

//sending matrix A

n=sendto(socketid,A,sizeof(A),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(n<0)
{
	printf("\nError in sending matrix A");
	exit(0);
}

//sending matrix B

n=sendto(socketid,B,sizeof(B),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(n<0)
{
	printf("\nError in sending matrix B");
	exit(0);
}

//receiving product matrix

if((n=recvfrom(socketid,C,sizeof(C),0,NULL,NULL))==-1)
{
	printf("\nCannot receive product matrix");
	exit(0);
}


printf("\nproduct Matrix:\n");
for(i=0;i<r1;i++)
{
	for(j=0;j<c2;j++)
	{
		printf("%d\t",C[i][j]);
	}
	printf("\n");
}

//close(socketid);








}
