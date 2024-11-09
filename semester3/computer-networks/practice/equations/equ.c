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

#define UDP_PORT 1234
#define TCP_PORT 5678
#define BUFFER_SIZE 1024

struct sockaddr_in setup_tcp_addr(int PORT) {
    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(PORT);
    tcp_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    return tcp_addr;
}

struct sockaddr_in setup_udp_addr(int PORT) {
    struct sockaddr_in udp_addr;
    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(PORT);
    udp_addr.sin_addr.s_addr = INADDR_ANY;
    return udp_addr;
}

void configure_udp_socket(int udp_sock, struct sockaddr_in udp_addr) {
    int broadcast = 1;
    if(setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt SO_BROADCAST failed");
        exit(1);
    }

    int reuse = 1;
    if(setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt SO_REUSEADDR failed");
        exit(1);
    }

    if (bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("UDP bind failed");
        exit(1);
    }
}

int main() {
    srand(time(NULL));

    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp_sock error");
        exit(1);
    }
    struct sockaddr_in udp_addr = setup_udp_addr(UDP_PORT);
    configure_udp_socket(udp_sock, udp_addr);

    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("tcp_sock error");
        exit(1);
    }
    struct sockaddr_in tcp_addr = setup_tcp_addr(TCP_PORT);
    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tcp connection failed");
        exit(1);
    }

    char recv_buffer[BUFFER_SIZE];
    char send_buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    memset(recv_buffer, 0, BUFFER_SIZE);  
    int bytes_received = recvfrom(udp_sock, recv_buffer, BUFFER_SIZE - 1, 0,
                            (struct sockaddr*) &server_addr, &addr_len);
   
    if(bytes_received < 0) {
        perror("error on receive");
        exit(1);
    }
   
    recv_buffer[bytes_received] = '\0';
    printf("Received equation: %s", recv_buffer);

    strcpy(send_buffer, "4\n");
    bytes_received = send(tcp_sock, send_buffer, strlen(send_buffer), 0);
    if(bytes_received < 0) {
        perror("error on send");
        exit(1);
    }

    memset(recv_buffer, 0, BUFFER_SIZE);  
    bytes_received = recv(tcp_sock, recv_buffer, BUFFER_SIZE - 1, 0);
   
    if(bytes_received < 0) {
        perror("error on receive");
        exit(1);
    }
   
    recv_buffer[bytes_received] = '\0';
    printf("Received mark: %s", recv_buffer);

    close(udp_sock);
    close(tcp_sock);
    return 0;
}