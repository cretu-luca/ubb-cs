#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define UDP_PORT 7777
#define TCP_PORT 1234
#define HOST "172.30.240.46"

int main() {
    int current_price = 0, my_offer = 0, max_price;
    char udp_buffer[1024];
    
    // Initialize random seed
    srand(time(NULL));
    max_price = rand() % 100 + 400;
    
    // Create UDP socket
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock == -1) {
        perror("Invalid UDP socket");
        exit(EXIT_FAILURE);
    }
    
    int broadcast = 1;
    if (setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, 
                   &broadcast, sizeof(broadcast)) < 0) {
        perror("Error setting broadcast option");
        close(udp_sock);
        exit(EXIT_FAILURE);
    }
    
    // Set up UDP address for binding
    struct sockaddr_in udp_bind_addr;
    memset(&udp_bind_addr, 0, sizeof(udp_bind_addr));
    udp_bind_addr.sin_family = AF_INET;
    udp_bind_addr.sin_port = htons(UDP_PORT);
    udp_bind_addr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind socket to listen for incoming broadcasts
    if(bind(udp_sock, (struct sockaddr*) &udp_bind_addr, sizeof(udp_bind_addr)) < 0) {
        perror("Cannot bind UDP socket");
        close(udp_sock);
        exit(EXIT_FAILURE);
    }
    
    printf("Listening for broadcasts on port %d\n", UDP_PORT);
    printf("Will make offers until price exceeds %d\n", max_price);
    
    while (current_price < max_price) {
        printf("Waiting for UDP message...\n");
        
        // Receive broadcast message
        struct sockaddr_in sender_addr;
        socklen_t addr_len = sizeof(sender_addr);
        ssize_t recv_len = recvfrom(udp_sock, udp_buffer, sizeof(udp_buffer)-1, 0,
                                  (struct sockaddr*) &sender_addr, &addr_len);
        
        if (recv_len < 0) {
            perror("Error receiving UDP message");
            close(udp_sock);
            exit(EXIT_FAILURE);
        }
        
        // Null terminate received data
        udp_buffer[recv_len] = '\0';
        
        current_price = atoi(udp_buffer);
        my_offer = current_price + rand() % 10;
        printf("Received current price: %d, My offer: %d\n", 
               current_price, my_offer);
    }
    
    close(udp_sock);
    return 0;
}