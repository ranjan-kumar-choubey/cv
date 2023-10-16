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
    /*SOCK_STREAM :Means TCP
    */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize socket structure
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));

     /* AF_INET is structure having */
    serv_addr.sin_family = AF_INET;
    //serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //string to integer
    serv_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    serv_addr.sin_port = htons(PORTNO); //host to netwrok sort : it is irrespective of little endian or big endian 
    // architecture; this gives architecture indendency

    // bind the host address using bind() call

   
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("ERROR on binding\n");
        exit(1);
    }

    // start listening for the clients,
    // here process will go in sleep mode and will wait for the incoming connection  
    // 5 :  indictaes that 5 network cient process in Queue 
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
    
    printf("IP address is: %s\n", inet_ntoa(cli_addr.sin_addr));
    printf("port is: %d\n", (int) ntohs(cli_addr.sin_port));

    // communication using read/write system calls until the client sends a "quit"
    char buffer[SIZE];
    while (1) {
        bzero(buffer, SIZE);
        int n = read(accepted_sockfd, buffer, SIZE-1);
        if (n < 0){
            perror("ERROR in reading from socket");
            exit(1);
        }
        if (n == 0) { // end of stream
            printf("client closed\n");
            break;
        }
        printf("client sent: %s\n", buffer);

        // scanf("%s", buffer);

        // echoing back
        n = write(accepted_sockfd, buffer, strlen(buffer));
        // n = write(accepted_sockfd, "bhaag bsdk...\n", strlen(buffer));
        if (n < 0){
            perror("ERROR in writing to socket");
            exit(1);
        }

        // stop this loop, if the client sends message "quit"
        if (!bcmp(buffer, "quit", 4))
            break;
    }

    close(accepted_sockfd);
    return 0;
}