#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main() {
    signal(SIGINT, intHandler);
    
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed\n");
        return 1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(1234);
    
    if (inet_pton(AF_INET, "192.168.1.143", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address\n");
        return 1;
    }
    
    printf("Attempting to connect...\n");
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed: %s\n", strerror(errno));
        return 1;
    }
    
    printf("Connected to server\n");
    
    while (keepRunning) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(sock, buffer, sizeof(buffer)-1);
        if (valread > 0) {
            printf("Received: %s\n", buffer);
        } else if (valread == 0) {
            printf("Server disconnected\n");
            break;
        } else {
            printf("Read error: %s\n", strerror(errno));
            break;
        }
    }
    
    printf("Closing connection...\n");
    close(sock);
    return 0;
}