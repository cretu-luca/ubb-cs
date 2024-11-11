// multi client server sends array of numbers over udp broadcast, clients sends 

// numar_de_elements;.......;
// sscanf("%d;%s", &numar_elements, &elemente)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define BUFFER_SIZE 64
#define IP "127.0.0.1"

int main() {
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp sock error");
        exit(1);
    }

    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(UDP_PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    int param = 1;
    if (setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &param, sizeof(param)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_REUSEPORT, &param, sizeof(param)) < 0 ||
        setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &param, sizeof(param)) < 0) {
        perror("setsockopt failed");
        close(udp_sock);
        exit(1);
    }

    if(bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("error on bind");
        exit(1);
    }

    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("error on tcp socket");
        exit(1);
    }

    struct sockaddr_in tcp_addr;
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);

    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("error on tcp connect");
        exit(1);
    }

    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);
    char buffer[BUFFER_SIZE], values[BUFFER_SIZE];
    int N;

    while(1) {
        int received = recvfrom(udp_sock, &buffer, BUFFER_SIZE, 0, (struct sockaddr*) &server_addr, &addr_size);
        if(received < 0) {
            perror("error on receive");
            exit(1);
        }

        buffer[received] = '\0';
        sscanf(buffer, "%d;%s", &N, values);
        printf("%d:", N);

        int values_int[N], sum = 0, prod = 1;

        for(int i = 0; i < N; i++) {
            sscanf(values, "%d;%s", &values_int[i], values); 
            printf("%d, ", values_int[i]);
            sum += values_int[i];
            prod *= values_int[i];
        }

        int option = rand() % 2;
        if(option == 0) {
            if(send(tcp_sock, &sum, sizeof(sum), 0) < 0) {
                perror("error on tcp send");
                exit(1);
            }
        } else {
            if(send(tcp_sock, &prod, sizeof(prod), 0) < 0) {
                perror("error on tcp send");
                exit(1);
            }
        }

        printf("\n");

        sleep(1);
    }
}