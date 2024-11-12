// does not work (there was some confusion around)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket < 0) {
        perror("udp socket error");
        exit(1);
    }

    int param = 1;
    if (setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(param)) < 0 ||
        setsockopt(udp_socket, SOL_SOCKET, SO_REUSEPORT, &param, sizeof(param)) < 0 ||
        setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &param, sizeof(param)) < 0) {
        perror("setsockopt error");
        close(udp_socket);
        exit(1);
    }

    struct sockaddr_in udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(udp_socket, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("binding error");
        exit(1);
    }

    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket < 0) {
        perror("udp socket error");
        exit(1);
    }

    struct sockaddr_in tcp_addr;
    memset(&udp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);

    if(connect(tcp_socket, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tcp socket error");
        exit(1);
    }

    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE], values[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    int N, primality;

    while(1) {
        int recv_len = recvfrom(udp_socket, buffer, BUFFER_SIZE, 0, 
            (struct sockaddr*) &server_addr, &addr_len);
        if(recv_len < 0) {
            perror("recvfrom error");
            exit(1);
        }
        
        buffer[recv_len] = '\0';

        sscanf(buffer, "%d;%s", &N, values);
        printf("[%d] ", N);

        int values_int[N], sum = 0;
        char temp_values[BUFFER_SIZE];
        strcpy(temp_values, values);

        for(int i = 0; i < N; i++) {
            sscanf(temp_values, "%d;%s", &values_int[i], temp_values);
            printf("%d, ", values_int[i]);
            sum += values_int[i];
        }
        printf("-> %d\n", sum);

        if(send(tcp_socket, &sum, sizeof(sum), 0) < 0) {
            perror("send error");
            break;
        }

        if(recv(tcp_socket, &primality, sizeof(primality), 0) < 0) {
            perror("recv error");
            exit(1);
        }

        if(primality == 1) {
            printf("%d is prime!\n", sum);
        } else {
            printf("%d is not prime!\n", sum);
        }
    }
}