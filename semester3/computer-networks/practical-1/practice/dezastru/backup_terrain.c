#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define port_udp 7777
#define port_tcp 1234
#define N 30
#define host "192.168.1.143"
#define MAX_RETRIES 5
#define RETRY_DELAY 2

void cleanup_socket(int* sock) {
    if (*sock != -1) {
        shutdown(*sock, SHUT_RDWR);
        close(*sock);
        *sock = -1;
    }
}

int create_tcp_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock != -1) {
        // Set TCP keepalive
        int keepalive = 1;
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
        
        // Set timeouts
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    }
    return sock;
}

int create_udp_socket() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock != -1) {
        int reuse = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
        
        // Set timeout
        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    }
    return sock;
}

int main() {
    srand(time(NULL));
    int udp_sock = -1, tcp_sock = -1;
    
    printf("Starting network client...\n");
    
    // Create sockets
    udp_sock = create_udp_socket();
    if (udp_sock == -1) {
        perror("Error creating UDP socket");
        return 1;
    }
    
    struct sockaddr_in udp_addr, tcp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    memset(&tcp_addr, 0, sizeof(tcp_addr));

    // Configure UDP
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(port_udp);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind UDP socket
    if (bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) == -1) {
        perror("Can't bind to UDP port");
        cleanup_socket(&udp_sock);
        return 1;
    }

    // Configure TCP address
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(port_tcp);
    if (inet_pton(AF_INET, host, &tcp_addr.sin_addr) <= 0) {
        perror("Invalid TCP address");
        cleanup_socket(&udp_sock);
        return 1;
    }

    printf("Attempting to connect to TCP server at %s:%d\n", host, port_tcp);
    
    // Connection attempt loop
    int connected = 0;
    int retries = 0;
    
    while (retries < MAX_RETRIES && !connected) {
        tcp_sock = create_tcp_socket();
        if (tcp_sock == -1) {
            perror("Error creating TCP socket");
            cleanup_socket(&udp_sock);
            return 1;
        }
        
        if (connect(tcp_sock, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr)) == 0) {
            connected = 1;
            printf("Successfully connected to TCP server\n");
            break;
        }
        
        printf("Connection attempt %d failed: %s\n", retries + 1, strerror(errno));
        cleanup_socket(&tcp_sock);
        sleep(RETRY_DELAY);
        retries++;
    }

    if (!connected) {
        perror("Failed to connect after all retries");
        cleanup_socket(&udp_sock);
        return 1;
    }

    char buff[N + 1];
    memset(buff, 'u', N);
    buff[N] = '\0';
    char *letters = "abcdefghijklmnopqrstuvwxyz";

    printf("Starting main loop...\n");
    
    while (1) {
        int index = rand() % N;
        while (buff[index] != 'u') {
            index = rand() % N;
        }

        int chary = rand() % 26;
        char buf[3];
        unsigned short idx = (unsigned short)index;
        buf[0] = (idx >> 8) & 0xFF;
        buf[1] = idx & 0xFF;
        buf[2] = letters[chary];

        printf("Sending - Index: %d, Char: %c\n", index, letters[chary]);
        
        if (send(tcp_sock, buf, 3, 0) == -1) {
            perror("TCP send failed");
            break;
        }

        buff[index] = letters[chary];
        
        socklen_t addr_len = sizeof(udp_addr);
        ssize_t recv_len = recvfrom(udp_sock, buff, N, 0,
                                  (struct sockaddr *)&udp_addr, &addr_len);
        
        if (recv_len == -1) {
            perror("Error receiving from UDP");
            break;
        }

        buff[recv_len] = '\0';
        printf("Received from broadcast: %s\n", buff);

        int has_unexplored = 0;
        for (int i = 0; i < N; i++) {
            if (buff[i] == 'u') {
                has_unexplored = 1;
                break;
            }
        }

        if (!has_unexplored) {
            printf("Array fully explored, shutting down...\n");
            break;
        }

        usleep(1000);
    }

    printf("Cleaning up...\n");
    cleanup_socket(&udp_sock);
    cleanup_socket(&tcp_sock);
    return 0;
}