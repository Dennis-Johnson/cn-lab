#include<stdio.h>
#include<strings.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

#define PORT 5000
#define MAXLINE 1000
#define BUFFER_LEN 100

int main(){
	char buffer[BUFFER_LEN];
	int servsockfd, len, n;
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));

	//Create UDP socket
	servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	
	//Bind server address to Socket descriptor
	bind(servsockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//Receive
	len = sizeof(cliaddr);
	n = recvfrom(servsockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
	buffer[n] = '\0';
	puts(buffer);

	//Echo back to client
	sendto(servsockfd, buffer, n, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	getchar();

	//Close the SD
	close(servsockfd);
	return 0;
}
