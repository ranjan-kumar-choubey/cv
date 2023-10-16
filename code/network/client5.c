#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <string.h>

#define PORT 54321
#define GROUP "234.5.6.7"
#define SIZE 256

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    // allow address reuse for binding multiple multicast applications to the same IP group address
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    
    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR bind");
        exit(1);
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
        &mreq, sizeof(mreq)) < 0) {
        perror("ERROR setsockopt mreq");
        exit(1);
    }

    char buffer[SIZE];
    socklen_t addrlen = sizeof(server_addr);
    while (1) {
        int n = recvfrom(sock, buffer, SIZE-1, 0,
            (struct sockaddr *)&server_addr, & addrlen);
        if (n < 0) {
            perror("ERROR recvfrom");
            exit(1);
        } else if (n == 0) { // EOF
            break;
        }
        printf("%s\n", buffer);
    }
}