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
    char buffer[SIZE];
    while (1) {
        printf("Enter a string: ");
        bzero(buffer, SIZE);
        scanf("%s", buffer);

        int n = write(sockfd, buffer, strlen(buffer));
        if (n < 0){
            perror("ERROR while writing to socket");
            exit(1);
        }

        // reply from server
        n = read(sockfd, buffer, SIZE-1);
        if (n < 0){
            perror("ERROR while reading from socket");
            exit(1);
        }
        printf("Server replied: %s \n", buffer);

        // stop this loop, if the server sends message "quit"
        if (!bcmp(buffer, "quit", 4))
            break;
    }

    close(sockfd);
    return 0;
}