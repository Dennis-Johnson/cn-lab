#include "common.h"

// UDP client

int main()
{
    int sockfd, running = 1;
    struct sockaddr_in serv_addr;
    char buffer[LEN_BUFFER];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Error creating datagram socket: ");
        exit(EXIT_FAILURE);
    }

    printf("Client running on port %d\n", PORT);
    while (running)
    {
        printf("Enter string to send to UDP server: ");
        scanf("%s", buffer);

        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        unsigned int serv_len = sizeof(serv_addr);
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv_addr, &serv_len);

        if (strncmp("end", buffer, 3) == 0)
            running = 0;
    }
    printf("Client shutting down!\n");
    return 0;
}
