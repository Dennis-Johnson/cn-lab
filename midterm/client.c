#include "common.h"

int main(){
	int sockfd;
	char ch = 'a';
	char buffer[LEN_BUFFER];

	struct sockaddr_in serv_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("Socket error: ");
		exit(EXIT_FAILURE);
	}
	else printf("Socket %d\n", sockfd);

	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
  // Alternate 172.16.224.17 or 172.16.57.152
	inet_aton("172.16.224.17", &(serv_addr.sin_addr));
	serv_addr.sin_port = PORT;
	printf("Converted back PORT: %d IP: %s\n",ntohs(serv_addr.sin_port), inet_ntoa(serv_addr.sin_addr));

	int con = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
  if(con == -1){
		perror("connect error: ");
		exit(EXIT_FAILURE);
	}
	
	printf("Connected to server on port %d\n", serv_addr.sin_port);

	printf("Char to send is %c\n", ch);
	write(sockfd, &ch, sizeof(char));

	strcpy(buffer, "");
	read(sockfd, buffer, sizeof(buffer));
	printf("Server sent %s\n", buffer);

	close(sockfd);
	return 0;
}
