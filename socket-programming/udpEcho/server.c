#include "common.h"

// Echoes back whatever client sends to this UDP server

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[LEN_BUFFER];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("Error creating socket: ");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("Error binding socket: ");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on PORT %d\n", PORT);
    while (1)
    {
        unsigned int cli_len = sizeof(cli_addr);
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_addr, &cli_len);

        printf("Recevied %s from client %d\n", buffer, ntohs(cli_addr.sin_port));

        //Echo same message back to client
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_addr, cli_len);

        if (strncmp(buffer, "end", 3) == 0)
            break;
    }

    printf("Server shutting down\n");
    return 0;
}
