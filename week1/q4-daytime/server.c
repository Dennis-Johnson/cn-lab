#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define PORT 4000
int main()
{
    int sockid = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockid < 0)
    {
        printf("Socket was not created.\n");
        exit(1);
    }

    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockid, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Bind failed.\n");
        exit(0);
    }

    char buffer[100];
    int len = sizeof(cliaddr);
    int n = recvfrom(sockid, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    struct tm *local;
    time_t t = time(NULL);
    local = localtime(&t);
    char reply[100], process[100];

    //buffer[0]='\0';
    strcpy(reply, "Server PID:");
    int p = getpid();
    sprintf(process, "%d", p);
    strcat(reply, process);

    strcat(reply, "\nDate & Time:");
    char *timee = asctime(local);
    strcat(reply, timee);
    //strcat(reply,"\nLocal Date & Time:");
    //timee=asctime(local);
    n = sendto(sockid, reply, strlen(reply), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    close(sockid);
}
