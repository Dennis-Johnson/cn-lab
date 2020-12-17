#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 4000
#define MAXLINE 1000
int arr[100][100];
int i = 0;

int main(){
    int buf[5];
    int servsockfd, len, n;
    struct sockaddr_in servaddr, cliaddr;
 
    bzero(&servaddr,sizeof(servaddr));
    servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(servsockfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
    len= sizeof(cliaddr);

    for(;;){
    	n = recvfrom(servsockfd,buf,sizeof(buf),0,(struct sockaddr*)&cliaddr,&len);
    	for(int j = 0;j<n;j++)
    	{
        	arr[i][j] = buf[j];
    	}
    	i++;
    	
	printf("Matrix is :\n");
    	for(int k =0;k<i;k++){
        	for(int j =0;j<5;j++){
            		printf("%d\t", arr[k][j]);
        	}
       		printf("\n");
    	}
    	sendto(servsockfd, buf, n, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    }
	getchar();   
 	close(servsockfd);
}
