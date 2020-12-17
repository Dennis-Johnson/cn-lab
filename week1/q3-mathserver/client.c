#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

#define PORT 4000

int main()
{
    int sockfd, sin_size, con;
    char operator;
    int op1, op2, result;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("socket created sucessfully\n");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    sin_size = sizeof(struct sockaddr_in);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sin_size) == 0)
        printf("Connected!\n");

    printf("Enter operator: +, -, *, /, %%:\n");
    scanf("%c", &operator);

    printf("Enter operands:\n");
    scanf("%d %d", &op1, &op2);

    write(sockfd, &operator, 10);
    write(sockfd, &op1, sizeof(op1));
    write(sockfd, &op2, sizeof(op2));
    read(sockfd, &result, sizeof(result));

    printf("Result = %d\n", result);
    close(sockfd);

    return 0;
}
