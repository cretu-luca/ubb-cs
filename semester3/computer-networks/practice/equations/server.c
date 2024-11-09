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
#include <pthread.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define BUFFER_SIZE 1024

typedef struct {
    int socket;
    struct sockaddr_in address;
} client_t;

int server_socket;

struct sockaddr_in setup_tcp_addr(int PORT) {
    struct sockaddr_in tcp_addr;
    memset(&tcp_addr, 0, sizeof(tcp_addr));
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(PORT);
    tcp_addr.sin_addr.s_addr = INADDR_ANY;

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
        exit(EXIT_FAILURE);
    }

    int reuse = 1;
    if(setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt SO_REUSEADDR failed");
        exit(EXIT_FAILURE);
    }

    if (bind(udp_sock, (struct sockaddr*) &udp_addr, sizeof(udp_addr)) < 0) {
        perror("UDP bind failed");
        exit(EXIT_FAILURE);
    }
}

void *handle_client(void *args) {
    client_t *client = (client_t *) args;
    char buffer[BUFFER_SIZE];

    int bytes_received = recv(client->socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
        printf("Client recv failed\n");
    } else {
        buffer[bytes_received] = '\0';
        printf("Received from %s:%d: %s\n",
                inet_ntoa(client->address.sin_addr),
                ntohs(client->address.sin_port),
                buffer);

        char response[] = "Mark: 10/10\n";
        send(client->socket, response, strlen(response), 0);
    }

    close(client->socket);
    free(client);
    return NULL;
}

void* broadcast_equations(void* args) {
    int udp_sock = *((int*)args);
    struct sockaddr_in broadcast_addr;
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(UDP_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    
    char equation[BUFFER_SIZE];
    while(1) {
        snprintf(equation, BUFFER_SIZE, "2 + 2 = ?\n");
        
        if(sendto(udp_sock, equation, strlen(equation), 0,
                 (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) < 0) {
            perror("Broadcast failed");
        } else {
            printf("Broadcast equation: %s", equation);
        }
        
        sleep(5);
    }
    return NULL;
}

void *handle_connections(void *args) {
    while(1) {
        client_t *client = malloc(sizeof(client_t));
        socklen_t addr_size = sizeof(client->address);

        client->socket = accept(server_socket, (struct sockaddr *) &client->address, &addr_size);
        if(client->socket < 0) {
            free(client);
            perror("accept error");
            continue;
        }

        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void *)client) != 0) {
            perror("client_thread error");
            close(client->socket);
            free(client);
            continue;
        }

        pthread_detach(thread);
        printf("new client connected from %s:%d\n", 
               inet_ntoa(client->address.sin_addr), 
               ntohs(client->address.sin_port));
    }

    return NULL;
}

int main() {
    srand(time(NULL));

    int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_sock < 0) {
        perror("udp_sock error");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in udp_addr = setup_udp_addr(UDP_PORT);
    configure_udp_socket(udp_sock, udp_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        perror("tcp_sock error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in tcp_addr = setup_tcp_addr(TCP_PORT);
    if(bind(server_socket, (struct sockaddr*) &tcp_addr, sizeof(tcp_addr)) < 0) {
        perror("tco bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_socket, 5) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }
    
    pthread_t middle_thread;
    if(pthread_create(&middle_thread, NULL, handle_connections, NULL) != 0) {
        perror("middle_thread error");
        exit(EXIT_FAILURE);
    }

    pthread_t broadcast_thread;
     if(pthread_create(&broadcast_thread, NULL, broadcast_equations, (void*) &udp_sock) != 0) {
        perror("Failed to create broadcast thread");
        exit(EXIT_FAILURE);
    }

    pthread_join(middle_thread, NULL);
    pthread_join(broadcast_thread, NULL);

    return 0;
}