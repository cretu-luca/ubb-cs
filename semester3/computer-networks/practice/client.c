#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 1235
#define BUFFER_SIZE 1024

int client_socket;
char buffer[BUFFER_SIZE];

int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);
    
    int broadcast = 1;
    int reuse = 1;

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));
    setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(PORT);

    bind(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr));

    printf("UDP Broadcast client is listening...\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &addr_len);
        
        if (bytes_received < 0) {
            perror("Receive failed");
            continue;
        }

        printf("Server: %s\nReceived: %s\n\n", 
               inet_ntoa(server_addr.sin_addr), buffer);
    }

    close(client_socket);
    return 0;
}