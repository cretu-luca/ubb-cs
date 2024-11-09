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

#define UDP_PORT 8890
#define TCP_PORT 8888
#define ARRAY_SIZE 10

struct packet {
    int index;
    char _char;
} __attribute__((packed));

struct buffer {
    char array[ARRAY_SIZE];
};

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

void configure_udp_sock(int udp_sock, struct sockaddr_in udp_addr) {
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
    // setting up TCP - create socket, create address, connect socket to address
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("tcp_fd error");
        exit(1);
    }

    struct sockaddr_in tcp_addr = setup_tcp_addr(TCP_PORT);
    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tcp connection failed");
        exit(1);
    }

    // setting up UDP - create socket, create address, configure socket, bind socket to address
    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp_soc error");
        exit(1);
    }

    struct sockaddr_in udp_addr = setup_udp_addr(UDP_PORT);
    configure_udp_sock(udp_sock, udp_addr);

    struct packet send_buffer;
    char receive_buffer[ARRAY_SIZE + 1]; 
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    
    int running = 1;
    while(running) {
        send_buffer.index = rand() % ARRAY_SIZE;
        send_buffer._char = 'a' + (rand() % 26);
        printf("Sending: index=%d char=%c\n", send_buffer.index, send_buffer._char);

        int bytes = send(tcp_sock, &send_buffer, sizeof(struct packet), 0);
        if(bytes < 0) {
            perror("Send error");
            exit(1);
        }

        bytes = recvfrom(udp_sock, receive_buffer, ARRAY_SIZE, 0, (struct sockaddr*) &server_addr, &addr_len);
        if(bytes < 0) {
            perror("Receive error");
            exit(1);
        }

        receive_buffer[bytes] = '\0';
        printf("Received buffer: %s\n", receive_buffer);

        running = 0;
        for(int i = 0; i < ARRAY_SIZE; i++) {
            if(receive_buffer[i] == 'u') {
                running = 1;
                break;
            }
        }
        usleep(100000);
    }

    printf("Closing connections...\n");
    close(udp_sock);
    close(tcp_sock);
    return 0;
}