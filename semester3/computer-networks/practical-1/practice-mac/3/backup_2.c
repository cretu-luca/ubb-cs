#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "192.168.1.143"

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Sending message to %s:%d\n", SERVER_IP, PORT);
    
    const char* message = "Hello from Mac!";
    sendto(sock, message, strlen(message), 0, 
           (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Message sent, waiting for response...\n");

    char buffer[1024] = {0};
    socklen_t server_len = sizeof(server_addr);
    
    // Set receive timeout
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int received = recvfrom(sock, buffer, 1024, 0,
                           (struct sockaddr*)&server_addr, &server_len);
    
    if (received < 0) {
        printf("No response received\n");
    } else {
        printf("Received: %s\n", buffer);
    }

    close(sock);
    return 0;
}