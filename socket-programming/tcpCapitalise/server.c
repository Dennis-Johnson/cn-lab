#include "common.h"

//Echo back whatever a client sends this TCP server

int main()
{
    struct sockaddr_in serv_addr, cli_addr;
    int sockfd, cli_sockfd;
    char buffer[LEN_BUFFER], IP[LEN_BUFFER];

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation error: ");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("Binding Error: ");
        exit(EXIT_FAILURE);
    }

    // Listen on bound socket, MAX 5 backlogs
    if (listen(sockfd, 5) == -1)
    {
        perror("Error listening: ");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on PORT %d\n", SERV_PORT);

    while (1)
    {
        memset(&cli_addr, 0, sizeof(cli_addr));
        unsigned int cli_len = sizeof(cli_addr);
        if ((cli_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len)) == -1)
        {
            perror("Error accepting client: ");
            exit(EXIT_FAILURE);
        };

        while (1)
        {
            read(cli_sockfd, buffer, sizeof(buffer));

            inet_ntop(AF_INET, &(cli_addr.sin_addr), IP, sizeof(IP));
            printf("Client IP: %s and PORT %d sent: %s\n", IP, ntohs(cli_addr.sin_port), buffer);

            for (int i = 0; i < strlen(buffer); i++)
                buffer[i] = toupper(buffer[i]);

            write(cli_sockfd, buffer, sizeof(buffer));

            if (strncmp(buffer, "QUIT", 4) == 0)
                break;
        }
        close(cli_sockfd);
    }
    close(sockfd);
    return 0;
}
