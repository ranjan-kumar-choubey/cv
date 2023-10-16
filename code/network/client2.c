#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>
#include <unistd.h>

#define IP "127.0.0.1" // change as required
#define PORTNO 54321 // change as required
#define SIZE 256 // change as required

int main(int argc, char *argv[]) {
    // create a socket and get file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize socket structure
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(PORTNO);

    // connect to server

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR while connecting");
        exit(1);
    }

    // communicating with read/write system calls
    uint32_t num;
    while (1) {
        printf("Enter an integer: ");
        // bzero(buffer, SIZE);
        scanf("%u", &num);
        uint32_t converted_num = htonl(num);

        int n = write(sockfd, &converted_num, sizeof(uint32_t));
        if (n < 0){
            perror("ERROR while writing to socket");
            exit(1);
        }

        // reply from server
        n = read(sockfd, &num, sizeof(uint32_t));
        if (n < 0){
            perror("ERROR while reading from socket");
            exit(1);
        }
        converted_num = ntohl(num);
        printf("Server replied: %u \n", converted_num);

        // stop this loop, if the server sends message 0
        if (converted_num == 0)
            break;
    }

    close(sockfd);
    return 0;
}