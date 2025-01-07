#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <string.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define BUFFER_SIZE 64

int main() {
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp port error");
        exit(1);
    }

    int param = 1;
    if (setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(param)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_REUSEPORT, &param, sizeof(param)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &param, sizeof(param)) < 0) {
        perror("setsockopt failed");
        close(udp_sock);
        exit(1);
    }

    struct sockaddr_in tcp_addr, udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("udp connect error");
        exit(1);
    }

    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("tcp port error");
        exit(1);
    }

    memset(&udp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = INADDR_ANY;

    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tcp connect error");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    int num1, num2;

    while(1) {
        int recv_len = recvfrom(udp_sock, buffer, BUFFER_SIZE, 0, 
            (struct sockaddr*) &server_addr, &addr_len);
        if(recv_len < 0) {
                perror("recvfrom error");
                exit(1);
            }

        buffer[recv_len] = '\0';
        sscanf(buffer, "%d,%d", &num1, &num2);
        printf("Received: < %d > and < %d >\n", num1, num2);

        int sum = num1 + num2;

        printf("Sending: %d\n", sum);

        if(send(tcp_sock, &sum, sizeof(sum), 0) < 0) {
            perror("send error");
            exit(1);
        }
    }
}