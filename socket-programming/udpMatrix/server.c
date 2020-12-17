#include "common.h"

// Echoes back whatever client sends to this UDP server

int mat_ind = -1;
int *matrix[MAX_ROWS];

void displayMatrix()
{
    printf("\nDisplay Matrix\n");
    if (mat_ind == -1)
    {
        printf("Empty Matrix\n");
        return;
    }

    for (int i = 0; i <= mat_ind; i++)
    {
        for (int j = 0; j < ROW_LEN; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    int buffer[ROW_LEN];

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
        size_t len_recvd = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_addr, &cli_len);

        if (len_recvd > 0)
        {
            mat_ind++;
            matrix[mat_ind] = calloc(ROW_LEN, sizeof(int));

            for (int i = 0; i < ROW_LEN; i++)
            {
                matrix[mat_ind][i] = buffer[i];
            }
            displayMatrix();
        }
    }

    printf("Server shutting down\n");
    return 0;
}
