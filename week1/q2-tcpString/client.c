#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define PORT 4000
#define sa struct sockaddr

int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in serv_addr;
    
		bzero(&serv_addr,sizeof(serv_addr));
    
		serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
		connect(sockfd,(sa*)&serv_addr,sizeof(serv_addr));
    
		char buffer[100],line[100];
    for(;;){
        printf("\nEnter a string or 'QUIT' to exit.\n");
        
				bzero(line,sizeof(line));
        bzero(buffer,sizeof(buffer));
        scanf("%s",line);
	
        write(sockfd,line,strlen(line));
        read(sockfd,buffer,sizeof(buffer));
        printf("\nServer says: %s\n",buffer);
        
				if(strncmp(buffer,"QUIT",4)==0)
            break;
    }
    
    close(sockfd);
    return 0;
}
