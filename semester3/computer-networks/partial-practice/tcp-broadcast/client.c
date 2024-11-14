#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define IP ""
#define UDP_PORT 1234
#define TCP_PORT 5678

int main() {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket < 0) {
        perror("error on tcp socket");
        exit(1);
    }

    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);

    if(connect(tcp_socket, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tcp socket error");
        exit(1);
    }
}