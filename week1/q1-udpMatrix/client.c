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
#define LEN_ARRAY 5

int main()
{
    int buffer[5];
    int arr[LEN_ARRAY] = {1, 1, 1, 1, 1};
    int sockfd, n, len;

    struct sockaddr_in servaddr, cliaddr;

    for (int i = 0; i < 5; i++)
    {
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);
        servaddr.sin_family = AF_INET;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        sendto(sockfd, arr, MAXLINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);

        printf("Sent row was: \t");
        for (int i = 0; i < LEN_ARRAY; ++i)
            printf("%d ", buffer[i]);

        //Update the row
        for (int i = 0; i < LEN_ARRAY; i++)
            arr[i]++;

        printf("\n");
    }
    close(sockfd);
}
