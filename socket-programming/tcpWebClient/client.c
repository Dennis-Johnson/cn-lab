#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SERVER_PORT 80
#define LEN_BUFFER 1024

int main()
{
  int sockfd;
  struct sockaddr_in serv_addr;

  char buffer[LEN_BUFFER];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_pton(AF_INET, "142.250.71.36", &serv_addr.sin_addr);
  serv_addr.sin_port = htons(SERVER_PORT);

  size_t len = sizeof(serv_addr);
  int result = connect(sockfd, (struct sockaddr *)&serv_addr, len);
  if (result == -1)
  {
    perror("\nClient Error: ");
    exit(EXIT_FAILURE);
  }

  char *request = "GET / HTTP / 1.1\r\nHost: www.google.com\r\n\r\n";
  write(sockfd, request, strlen(request));

  size_t len_read = 0;
  printf("Response is\n");
  do
  {
    memset(buffer, '\0', sizeof(buffer));
    len_read = read(sockfd, buffer, sizeof(buffer));
    printf("%s\n", buffer);
  } while (len_read > 0);

  close(sockfd);
  return 0;
}
