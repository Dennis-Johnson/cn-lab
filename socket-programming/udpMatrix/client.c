#include "common.h"

// UDP client that sends rows of integers to the server
int row[] = {0, 0, 0, 0};

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
        printf("Enter %d numbers in a row to send to UDP server: ", ROW_LEN);
        scanf("%d %d %d %d", &row[0], &row[1], &row[2], &row[3]);

        sendto(sockfd, row, sizeof(row), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

        printf("Enter y to continue, 'end' to quit: ");
        scanf("%s", buffer);

        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
    }
    printf("Client shutting down!\n");
    return 0;
}
