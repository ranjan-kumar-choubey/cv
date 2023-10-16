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
    
    struct sockaddr_in group_addr;
    bzero((char *) &group_addr, sizeof(group_addr));

    group_addr.sin_family = AF_INET;
    group_addr.sin_port = htons(PORT);
    // group_addr.sin_addr.s_addr = INADDR_ANY;
    group_addr.sin_addr.s_addr = inet_addr(GROUP);

    char buffer[SIZE];
    while (1) {
        printf("Enter a string: ");
        scanf("%s", buffer);
        int n = sendto(sock, buffer, strlen(buffer), 0,
            (struct sockaddr *)&group_addr, sizeof(group_addr));
        if (n < 0) {
            perror("ERROR sendto");
            exit(1);
        }
    }
}