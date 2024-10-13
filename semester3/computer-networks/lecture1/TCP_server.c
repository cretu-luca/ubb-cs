#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_PORT 1500
#define MAX_MSG 100
#define ERROR -1

int main(int argc, char *argv[]) {
    int sd, newSd, cliLen;
    struct sockaddr_in cliAddr, servAddr;
    char line[MAX_MSG];
    int len;

    /* Create socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("cannot open socket");
        return ERROR;
    }

    /* Bind server port */
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(SERVER_PORT);
    if (bind(sd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("cannot bind port");
        return ERROR;
    }

    listen(sd, 5);
    printf("Server: waiting for data on port TCP %u\n", SERVER_PORT);

    while (1) {
        cliLen = sizeof(cliAddr);
        newSd = accept(sd, (struct sockaddr *)&cliAddr, &cliLen);
        if (newSd < 0) {
            perror("cannot accept connection");
            continue;
        }

        /* Initialize line */
        memset(line, 0, MAX_MSG);

        /* Receive message from client */
        len = read(newSd, line, MAX_MSG);
        if (len > 0) {
            printf("Server: received from %s:TCP%d : %s\n",
                inet_ntoa(cliAddr.sin_addr),
                ntohs(cliAddr.sin_port), line);

            /* Echo message back to client */
            write(newSd, line, len);
        } else {
            printf("Error receiving data\n");
        }
        
        close(newSd);
    }

    close(sd);
    return 0;
}
