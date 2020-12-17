#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#define PORT 4000

int main(){
    int sockid=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in servaddr,server_state;  
    
    bzero(&servaddr,sizeof(servaddr));  
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);


    char buffer[100];
    char *msg="Request: Current Date and Time\n";
    
    int data_len = sendto(sockid, msg, strlen(msg), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    
    int len=sizeof(server_state);
    data_len = recvfrom(sockid, buffer, sizeof(buffer), 0, (struct sockaddr*)&server_state, &len);
    buffer[data_len]='\0';

    printf("SERVER with IP Address %s and Port Number %d sends %s",inet_ntoa(server_state.sin_addr), ntohs(server_state.sin_port), buffer);
    
    close(sockid);
    return 0;
}
