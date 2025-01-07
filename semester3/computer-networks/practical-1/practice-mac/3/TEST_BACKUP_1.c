#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdint.h>

#define UDP_PORT 1234
#define TCP_PORT 5678
#define BUFFER_SIZE 1024
#define SERVER_IP "192.168.1.143"  // Your Windows machine IP
#define BROADCAST_ADDR "255.255.255.255"

int setup_udp_socket() {
   int udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
   if (udp_sock < 0) {
       perror("UDP socket creation failed");
       exit(1);
   }

   struct sockaddr_in udp_addr;
   memset(&udp_addr, 0, sizeof(udp_addr));
   udp_addr.sin_family = AF_INET;
   udp_addr.sin_port = htons(UDP_PORT);
   udp_addr.sin_addr.s_addr = INADDR_ANY;

   int broadcast = 1;
   if (setsockopt(udp_sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
       perror("UDP setsockopt SO_BROADCAST failed");
       close(udp_sock);
       exit(1);
   }

   int reuse = 1;
   if (setsockopt(udp_sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
       perror("UDP setsockopt SO_REUSEADDR failed");
       close(udp_sock);
       exit(1);
   }

   if (bind(udp_sock, (struct sockaddr*)&udp_addr, sizeof(udp_addr)) < 0) {
       perror("UDP bind failed");
       close(udp_sock);
       exit(1);
   }

   printf("UDP socket bound successfully\n");
   return udp_sock;
}

int setup_tcp_socket() {
   int tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
   if (tcp_sock < 0) {
       perror("TCP socket creation failed");
       return -1;
   }

   struct sockaddr_in tcp_addr;
   memset(&tcp_addr, 0, sizeof(tcp_addr));
   tcp_addr.sin_family = AF_INET;
   tcp_addr.sin_port = htons(TCP_PORT);
   tcp_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

   printf("Attempting TCP connection to %s:%d\n", SERVER_IP, TCP_PORT);
   
   if (connect(tcp_sock, (struct sockaddr*)&tcp_addr, sizeof(tcp_addr)) < 0) {
       printf("TCP connection failed to %s:%d\n", SERVER_IP, TCP_PORT);
       perror("Error details");
       close(tcp_sock);
       return -1;
   }

   printf("TCP connection established\n");
   return tcp_sock;
}

int calculate_sum(char* buffer) {
   int sum = 0;
   char* token;
   int first = 1;
   int count = 0;
   int N = 0;
   char* temp_buffer = strdup(buffer);  // Create a copy of buffer for strtok

   if (temp_buffer == NULL) {
       printf("Memory allocation failed\n");
       return 0;
   }

   token = strtok(temp_buffer, ";");
   while (token != NULL) {
       if (first) {
           N = atoi(token);
           first = 0;
       } else {
           sum += atoi(token);
           count++;
       }
       token = strtok(NULL, ";");
   }

   free(temp_buffer);  // Free the temporary buffer

   if (count != N) {
       printf("Warning: Expected %d numbers but got %d\n", N, count);
   }

   return sum;
}

void int_to_bytes(int value, unsigned char bytes[4]) {
   bytes[0] = (value >> 0) & 0xFF;
   bytes[1] = (value >> 8) & 0xFF;
   bytes[2] = (value >> 16) & 0xFF;
   bytes[3] = (value >> 24) & 0xFF;
}

int main() {
   printf("Starting client...\n");
   
   int udp_sock = setup_udp_socket();
   printf("UDP socket set up successfully\n");
   
   int retry_count = 0;
   int tcp_sock;
   while (retry_count < 5) {
       tcp_sock = setup_tcp_socket();
       if (tcp_sock >= 0) {
           printf("TCP socket connected successfully\n");
           break;
       }
       printf("TCP connection failed, retrying in 2 seconds (attempt %d/5)...\n", retry_count + 1);
       sleep(2);
       retry_count++;
   }
   
   if (retry_count >= 5) {
       printf("Failed to establish TCP connection after 5 attempts\n");
       close(udp_sock);
       exit(1);
   }

   char buffer[BUFFER_SIZE];
   struct sockaddr_in sender_addr;
   socklen_t sender_len = sizeof(sender_addr);

   printf("Client started. Listening for UDP broadcasts...\n");

   while (1) {
       memset(buffer, 0, BUFFER_SIZE);
       
       printf("Waiting for UDP broadcast...\n");
       int recv_len = recvfrom(udp_sock, buffer, BUFFER_SIZE-1, 0,
                              (struct sockaddr*)&sender_addr, &sender_len);
       
       if (recv_len < 0) {
           perror("UDP receive failed");
           continue;
       }
       
       buffer[recv_len] = '\0';
       printf("Received broadcast from %s: %s\n", 
              inet_ntoa(sender_addr.sin_addr), buffer);

       int sum = calculate_sum(buffer);
       printf("Calculated sum: %d\n", sum);

       unsigned char bytes[4];
       int_to_bytes(sum, bytes);
       
       printf("Sending sum %d to server...\n", sum);
       if (send(tcp_sock, bytes, sizeof(bytes), 0) < 0) {
           perror("TCP send failed");
           printf("Attempting to reconnect TCP...\n");
           
           close(tcp_sock);
           retry_count = 0;
           while (retry_count < 5) {
               tcp_sock = setup_tcp_socket();
               if (tcp_sock >= 0) {
                   printf("TCP reconnection successful\n");
                   break;
               }
               printf("TCP reconnection failed, retrying in 2 seconds (attempt %d/5)...\n", retry_count + 1);
               sleep(2);
               retry_count++;
           }
           
           if (retry_count >= 5) {
               printf("Failed to reestablish TCP connection\n");
               break;
           }
           continue;
       }
       printf("Sent sum to server via TCP successfully\n");
   }

   close(udp_sock);
   close(tcp_sock);
   return 0;
}