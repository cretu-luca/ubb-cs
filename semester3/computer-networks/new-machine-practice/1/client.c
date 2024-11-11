// server broadcasts pairs of random numbers, each client sends back
// sum of numbers 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define IP "0.0.0.0"
#define BUFFER_SIZE 64

int main() {
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp_sock error");
        exit(1);
    }

    int one = 1;
    if (setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &one, sizeof(one)) < 0) {
        perror("setsockopt failed");
        close(udp_sock);
        exit(1);
    }

    struct sockaddr_in udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("binding error");
        close(udp_sock);
        exit(1);
    }
    printf("UDP connection established\n");

    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("tcp_sock error");
        exit(1);
    }

    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("error on connection");
        exit(1);
    }

    printf("Client started. Waiting for broadcasts...\n");

    char buffer[BUFFER_SIZE];
    struct sockaddr_in sender_addr;
    socklen_t addr_len = sizeof(sender_addr);
    int num1, num2;

    while(1) {
        int recv_len = recvfrom(udp_sock, buffer, sizeof(buffer), 0, (struct sockaddr*) &sender_addr, &addr_len);
        if(recv_len < 0) {
            perror("error on udp receive");
            exit(1);
        }

        buffer[recv_len] = '\0';
        sscanf(buffer, "%d,%d", &num1, &num2);
        printf("Received: {%d} and {%d}\n", num1, num2);

        int sum = num1 + num2;
        if(send(tcp_sock, &sum, sizeof(sum), 0) < 0) {
            perror("error on send");
            exit(1);
        }
        printf("Sending: %d\n", sum);
        usleep(1);
    }

    close(udp_sock);
}