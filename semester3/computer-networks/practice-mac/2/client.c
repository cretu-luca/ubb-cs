// no broadcasting - server sends [] over TCP, client sends [] over UDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define UDP_PORT 1234
#define TCP_PORT 5678

int main() {
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp sock error");
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

    struct sockaddr_in udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
/*
    if(bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("udp bind error");
        exit(1);
    }
*/

    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("tcp sock error");
        exit(1);
    }

    char *message = "hello - this is client.";
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TCP_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t addr_len = sizeof(server_addr);
    
    char buffer[64];

    while(1) {
        if(sendto(udp_sock, message, strlen(message), 0, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
            perror("error on udp send");
            exit(1);
        }

        if(connect(tcp_sock, (struct sockaddr*) &server_addr, addr_len) < 0) {
            perror("tcp socket error");
            exit(1);
        }

        int received = recv(tcp_sock, buffer, sizeof(buffer) - 1, 0);
        if(received < 0) {
            perror("error on tcp recv");
            exit(1);
        }

        buffer[received] = '\0';
        printf("Received: %s\n", buffer);

        tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(tcp_sock < 0) {
            perror("tcp sock error");
            exit(1);
        }

        sleep(1);
    }
}