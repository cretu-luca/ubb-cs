#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>   // for srand(time(NULL))

#define host "127.0.0.1"
#define port 1234

int running = 1;

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Create UDP socket
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket == -1) {
        perror("udp socket error");
        exit(1);
    }
    
    // Enable broadcast capability
    int broadcast = 1;
    if(setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1) {
        perror("setsockopt broadcast error");
        close(udp_socket);
        exit(1);
    }

    // Enable address reuse
    int reuse = 1;
    if(setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("setsockopt reuse error");
        close(udp_socket);
        exit(1);
    }
   
    // Setup UDP address
    struct sockaddr_in udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(port);
    udp_addr.sin_addr.s_addr = inet_addr(host);

    // Create TCP socket
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket == -1) {
        perror("tcp socket error");
        close(udp_socket);
        exit(1);
    }
   
    // Setup TCP address
    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(port);
    tcp_addr.sin_addr.s_addr = inet_addr(host);

    // Connect TCP socket
    if(connect(tcp_socket, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) == -1) {
        perror("error in tcp connect");
        close(udp_socket);
        close(tcp_socket);
        exit(1);
    }

    printf("Connected to server successfully\n");

    while(running) {
        float pi_approx;
        int bytes_received = recv(tcp_socket, &pi_approx, sizeof(float), 0);
        if (bytes_received <= 0) {
            printf("Server disconnected. Shutting down...\n");
            running = 0;
            break;
        }
        printf("Received π approximation: %.6f\n", pi_approx);

        int n1 = rand() % 100;
        int n2 = rand() % 100;
        char buff[7];
        snprintf(buff, sizeof(buff), "%d;%d", n1, n2);
        
        printf("Sending points: %d;%d\n", n1, n2);
        
        if(sendto(udp_socket, buff, sizeof(buff), 0,
                 (struct sockaddr*) &udp_addr, sizeof(udp_addr)) == -1) {
            perror("error on send to udp");
            running = 0;
            break;
        }
        
        usleep(10000);  // Sleep for 10ms to prevent overwhelming the server
    }

    close(udp_socket);
    close(tcp_socket);
    return 0;
}