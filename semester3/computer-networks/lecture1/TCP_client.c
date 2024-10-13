#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */

#define SERVER_PORT 1500
#define MAX_MSG 100

int main(int argc, char *argv[]) {
    int sd, rc;
    struct sockaddr_in servAddr;
    struct hostent *h;
    char msg[MAX_MSG];

    if (argc < 3) {
        printf("usage: %s <server> <text>\n", argv[0]);
        exit(1);
    }

    h = gethostbyname(argv[1]);
    if (h == NULL) {
        printf("%s: unknown host '%s'\n", argv[0], argv[1]);
        exit(1);
    }

    servAddr.sin_family = h->h_addrtype;
    memcpy((char *)&servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    servAddr.sin_port = htons(SERVER_PORT);

    /* Create socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("cannot open socket");
        exit(1);
    }

    /* Connect to server */
    rc = connect(sd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (rc < 0) {
        perror("cannot connect");
        close(sd);
        exit(1);
    }

    /* Send message to server */
    write(sd, argv[2], strlen(argv[2]) + 1);

    /* Receive response from server */
    read(sd, msg, sizeof(msg));
    printf("Received back: %s\n", msg);

    close(sd);
    return 0;
}
