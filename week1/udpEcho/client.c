#include<stdio.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 5000
#define MAXLINE 1000

int main(){
	char buffer[100];
	char *message = "Hello Server";
	int sockfd, n, len;
	struct sockaddr_in servaddr, cliaddr;

	//Clear servaddr
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	//Create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	len = sizeof(cliaddr);

	//Wait for response
	n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
	buffer[n] = '\0';
	printf("Message from server: %s\n", buffer);
	getchar();
	
	//Close the desciptor
	close(sockfd);
	return 0;
}
