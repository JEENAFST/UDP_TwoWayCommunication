//UDP Server program
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>



int main(int argc, char **argv){



  if (argc != 2){

    printf("Usage: %s <port>\n", argv[0]); //./server 2000

    exit(0);

  }



  char *ip = "127.0.0.1";

  int port = atoi(argv[1]);// PORT Number will be the command line argument



  int sockfd;

  struct sockaddr_in server_addr, client_addr; 

  char buffer[1024];

  socklen_t addr_size;

  int n;

 //socket creation

 //int socket(int domain, int type, int protocol);

  sockfd = socket(AF_INET,SOCK_DGRAM, 0);

  if (sockfd < 0){

    perror("[-]socket error");

    exit(1);

  }



  memset(&server_addr, '\0', sizeof(server_addr)); //clearing the memory space of the server_addr variable

  server_addr.sin_family = AF_INET; //Internet protocol selected

  server_addr.sin_port = htons(port);/*The htons() function converts the unsigned short integer hostshort from host byte order to network byte order */

  server_addr.sin_addr.s_addr = inet_addr(ip);/* inter_addr :function converts the Internet host address server_ip from IPv4 numbers-and-dots notation into binary data in network byte order */



  n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

  if (n < 0) {

    perror("[-]bind error");

    exit(1);

  }



  bzero(buffer, 1024);

  addr_size = sizeof(client_addr);

  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);

  printf("[+]Data recv: %s\n", buffer);



  bzero(buffer, 1024);

  strcpy(buffer, "Hai from UDP server");

  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

  printf("[+]Data send: %s\n", buffer);



  return 0;

}
