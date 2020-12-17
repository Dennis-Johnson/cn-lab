#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<ctype.h>

#define PORT 4000
#define sa struct sockaddr

int main(){
    int sockid = socket(AF_INET,SOCK_STREAM,0);
    int sockid_state;
 
    unsigned int len = 0;
		char buffer[100];
    struct sockaddr_in serv_addr,cli_addr;
    
		bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    
		if(bind(sockid, (sa*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("Error binding socket");
        exit(1);
    }
 
    listen(sockid,5);
		
		len = sizeof(cli_addr);
    sockid_state = accept(sockid, (sa*)&cli_addr, &len);

    for(;;)
    {
        bzero(buffer,sizeof(buffer));
        read(sockid_state, buffer, sizeof(buffer));
        printf("\nClient IP %s and Port %d sent: %s",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port),buffer);
        
				for(int i=0;i<strlen(buffer);i++)
					buffer[i]=toupper(buffer[i]);
        
				//Respond with capitals
				write(sockid_state, buffer, sizeof(buffer));
        if(strncmp(buffer,"QUIT", 4)==0) 
					break;
    }
	
    printf("\nServer Closing\n");
    close(sockid);
    return 0;
}
