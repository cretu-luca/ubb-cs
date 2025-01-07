#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    while(1) {
        printf("Enter message (or 'quit' to exit): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strcmp(buffer, "quit") == 0)
            break;
        
        sendto(sock, buffer, strlen(buffer), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        int len = sizeof(server_addr);
        int n = recvfrom(sock, buffer, BUFFER_SIZE, 0,
                        (struct sockaddr*)&server_addr, &len);
        buffer[n] = '\0';
        
        printf("Server reply: %s\n", buffer);
    }
    
    close(sock);
    return 0;
}