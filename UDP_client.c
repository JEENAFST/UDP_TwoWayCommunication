#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>



int main(int argc, char **argv){



  if (argc != 2) {

    printf("Usage: %s <port>\n", argv[0]); //./client 2000

    exit(0);

  }



  char *ip = "127.0.0.1";// local host ip

  int port = atoi(argv[1]);// conver to integer



  int sockfd;

  struct sockaddr_in addr;

  char buffer[1024];

  socklen_t addr_size;



  sockfd = socket(AF_INET, SOCK_DGRAM,0);

  memset(&addr, '\0', sizeof(addr));// clearing the memory space of the variable addr

  addr.sin_family = AF_INET;

  addr.sin_port = htons(port);//

  addr.sin_addr.s_addr = inet_addr(ip);



  bzero(buffer, 1024);// Erasing 1024 bytes before using the buffer

  strcpy(buffer, "Hello, World!");

  //

  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));

  printf("[+]Data send: %s\n", buffer);



  bzero(buffer, 1024);

  addr_size = sizeof(addr);

  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);

  printf("[+]Data recv: %s\n", buffer);



  return 0;

}
