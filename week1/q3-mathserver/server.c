#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 4000

void main()
{
    int b, sockfd, connfd, sin_size, l, n, len;
    char operator;
    int op1, op2, result;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("socket created sucessfully\n");
    struct sockaddr_in servaddr, clientaddr;

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == 0)
        printf("bind sucessful\n");
    if ((listen(sockfd, 5)) == 0)
        printf("listen sucessful\n");
    sin_size = sizeof(struct sockaddr_in);
    while (1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &sin_size);
        if (connfd > 0)
            printf("accept sucessful\n");
        int pid = fork();
        if (pid == 0)
        {
            read(connfd, &operator, 10);
            read(connfd, &op1, sizeof(op1));
            read(connfd, &op2, sizeof(op2));
            switch (operator)
            {
            case '+':
                result = op1 + op2;
                printf("Result is: %d + %d = %d\n\n", op1, op2, result);
                break;
            case '-':
                result = op1 - op2;
                printf("Result is: %d - %d = %d\n\n", op1, op2, result);
                break;
            case '*':
                result = op1 * op2;
                printf("Result is: %d * %d = %d\n\n", op1, op2, result);
                break;
            case '/':
                result = op1 / op2;
                printf("Result is: %d / %d = %d\n\n", op1, op2, result);
                break;
            case '%':
                result = op1 % op2;
                printf("Result is: %d % %d = %d\n\n", op1, op2, result);
                break;
            default:
                printf("ERROR: Unsupported Operation");
            }

            write(connfd, &result, sizeof(result));
            exit(0);
        }
        else
            close(connfd);
    }
}
