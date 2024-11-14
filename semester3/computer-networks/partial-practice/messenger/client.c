#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>

#define TCP_PORT 1234
#define IP "172.20.10.14"
#define BUFFER_SIZE 1024

int running = 1;
int tcp_sock; 

void* receive_messages(void* arg) {
    char buffer[BUFFER_SIZE];
    
    while (running) {
        memset(buffer, 0, BUFFER_SIZE);
        int recv_len = recv(tcp_sock, buffer, BUFFER_SIZE - 1, 0);
        
        if (recv_len <= 0) {
            if (recv_len == 0) {
                printf("Server disconnected\n");
            } else if (running) {
                perror("Error receiving message");
            }
            running = 0;
            break;
        }
        
        buffer[recv_len] = '\0';
        printf("Received: %s\n", buffer);
    }
    
    return NULL;
}

void handle_signal(int sig) {
    running = 0;
    if (tcp_sock > 0) {
        shutdown(tcp_sock, SHUT_RDWR);
    }
}

int main() {
    // Set up signal handling for graceful shutdown
    signal(SIGINT, handle_signal);
    
    // Create socket
    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    
    // Set up server address structure
    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);
    
    // Connect to server
    if (connect(tcp_sock, (struct sockaddr*)&tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("Connection failed");
        close(tcp_sock);
        exit(1);
    }
    
    printf("Connected to server at %s:%d\n", IP, TCP_PORT);
    
    // Create receiver thread
    pthread_t recv_thread;
    if (pthread_create(&recv_thread, NULL, receive_messages, NULL) != 0) {
        perror("Failed to create receiver thread");
        close(tcp_sock);
        exit(1);
    }
    
    // Main loop for sending messages
    char buffer[BUFFER_SIZE];
    while (running) {
        // Clear input buffer
        memset(buffer, 0, BUFFER_SIZE);
        
        // Read input (non-blocking)
        if (fgets(buffer, BUFFER_SIZE - 1, stdin) != NULL) {
            // Remove trailing newline
            buffer[strcspn(buffer, "\n")] = 0;
            
            // Check for exit command
            if (strcmp(buffer, "quit") == 0) {
                running = 0;
                break;
            }
            
            // Send message
            if (running && send(tcp_sock, buffer, strlen(buffer), 0) < 0) {
                perror("Failed to send message");
                running = 0;
                break;
            }
        }
    }
    
    // Cleanup
    printf("\nClosing connection...\n");
    shutdown(tcp_sock, SHUT_RDWR);
    close(tcp_sock);
    pthread_join(recv_thread, NULL);
    
    return 0;
}