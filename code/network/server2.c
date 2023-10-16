#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>
#include <unistd.h>

#define PORTNO 54321 // change as required
#define SIZE 256 // change as required

int main(int argc, char **argv) {
    
    // create a socket and get file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize socket structure
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORTNO);

    // bind the host address using bind() call
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("ERROR on binding\n");
        exit(1);
    }

    // start listening for the clients,
    // here process will go in sleep mode and will wait for the incoming connection
    if (listen(sockfd, 5) < 0) {
        perror("Listen error");
        exit(3);
    }
    printf("server started listening in port %d\n", PORTNO);

    // accept actual connection from the client
    struct sockaddr_in cli_addr;
    int cli_addr_len = sizeof(cli_addr);
    int accepted_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
    printf("connection established to a client\n");
    
    // printf("IP address is: %s\n", inet_ntoa(cli_addr.sin_addr));
    // printf("port is: %d\n", (int) ntohs(cli_addr.sin_port));

    // communication using read/write system calls until the client sends a "quit"
    uint32_t num, converted_num;
    while (1) {
        
        int n = read(accepted_sockfd, &num, sizeof(uint32_t));
        if (n < 0){
            perror("ERROR in reading from socket");
            exit(1);
        }
        if (n == 0) { // end of stream
            printf("client closed\n");
            break;
        }
        converted_num = ntohl(num);
        printf("client sent: %u\n", converted_num);

        num = converted_num + 1;
        converted_num = htonl(num);

        // echoing back
        n = write(accepted_sockfd, &converted_num, sizeof(uint32_t));
        if (n < 0){
            perror("ERROR in writing to socket");
            exit(1);
        }

        // stop this loop, if the client sends -1 and server replies 0
        if (num == 0)
            break;
    }

    close(accepted_sockfd);
    return 0;
}