#include "common.h"

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[LEN_BUFFER], read_buffer[LEN_BUFFER];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Error creating socket: ");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("Error connecting to server: ");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        strcpy(buffer, "");
        printf("Enter a string to send to the server: ");
        scanf("%s", buffer);

        size_t len_written = 0;
        if ((len_written = write(sockfd, buffer, sizeof(buffer))) < 0)
        {
            perror("Error writing to socket: ");
        }

        strcpy(read_buffer, "");
        read(sockfd, read_buffer, sizeof(buffer));
        printf("Server replied: %s\n", read_buffer);

        if (strncmp(buffer, "quit", 4) == 0)
        {
            printf("Client shutting down!\n");
            break;
        }
    }

    return 0;
}
