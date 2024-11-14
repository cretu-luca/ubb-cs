#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <math.h>
#include <time.h>

#define IP "172.20.10.14"
#define TCP_PORT 1234
#define BUFFER_SIZE 1024

void shuffle_chars(char *arr, int length) {
    for (int i = length - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    srand(time(NULL));
    
    // Create socket
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("socket error");
        exit(1);
    }

    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);

    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("connect error");
        exit(1);
    }

    char buffer[BUFFER_SIZE], recv_buffer[2];
    int recv_len;
    
    recv_len = recv(tcp_sock, buffer, sizeof(buffer) - 1, 0);
    if(recv_len < 0) {
        perror("recv error");
        exit(1);
    }
    buffer[recv_len] = '\0';
    printf("Received: %s\n", buffer);

    int tries = 0, total_attemps = pow(26, strlen(buffer));
    while(strcmp(recv_buffer, "Y") && tries < total_attemps) {
        printf("Try %d: ", tries);
        
        shuffle_chars(buffer, recv_len);
        printf("Sending: %s\n", buffer);

        if(send(tcp_sock, buffer, recv_len, 0) < 0) {
            perror("send error");
            break;
        }

        int recc = recv(tcp_sock, recv_buffer, sizeof(recv_buffer) - 1, 0);
        if(recc < 0) {
            perror("recv error");
            exit(1);
        }
        recv_buffer[recc] = '\0';
        printf("Response: %s\n", recv_buffer);

        tries++;
    }

    close(tcp_sock);
    return 0;
}