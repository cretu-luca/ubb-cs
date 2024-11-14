#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define IP "172.20.10.14"
#define TCP_PORT 1234
#define BUFFER_SIZE 1024

int guesses[100];

int main() {
    srand(time(NULL));
    
    memset(guesses, 0, sizeof(guesses));
    
    int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_sock < 0) {
        perror("error on tcp sock");
        exit(1);
    }
    
    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(TCP_PORT);
    tcp_addr.sin_addr.s_addr = inet_addr(IP);
    
    if(connect(tcp_sock, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("error on connect");
        exit(1);
    }

    
    char buffer[BUFFER_SIZE];
    char guess_str[16];
    
    while(1) {
        memset(buffer, 0, sizeof(buffer));
        memset(guess_str, 0, sizeof(guess_str));

        int guess = rand() % 100;
        while(guesses[guess] != 0) {
            guess = rand() % 100;
        }
        guesses[guess] = 1;
        
        snprintf(guess_str, sizeof(guess_str), "%d", guess);
        printf("Sending guess: %s", guess_str);
        
        if(send(tcp_sock, guess_str, strlen(guess_str), 0) < 0) {
            perror("error on send");
            exit(1);
        }

        int recv_len = recv(tcp_sock, buffer, sizeof(buffer), 0);
        if(recv_len < 0) {
            perror("error on recv");
            exit(1);
        }
        buffer[recv_len] = '\0';
        printf("Received: %s\n\n", buffer);

        if(strcmp(buffer, "D") == 0) {
            printf("EZ MESSY %s", guess_str);
            close(tcp_sock);
            exit(1);
        }

        sleep(1);
    }
    
    close(tcp_sock);
    return 0;
}