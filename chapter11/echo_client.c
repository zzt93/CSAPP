//
// Created by zzt on 11/22/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "csapp.h"

#define MAX 1024

int main(int argc, char **argv) {
    int clientfd, port;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    char *host = argv[1];
    port = atoi(argv[2]);

    clientfd = Open_clientfd(host, port);
    rio_t rio;
    Rio_readinitb(&rio, clientfd);

    char line[MAX];
    while (Fgets(line, MAX, stdin) != NULL) {
        Rio_writen(clientfd, line, strlen(line));
        Rio_readlineb(&rio, line, MAX);
        Fputs(line, stdout);
    }
    Close(clientfd);
    exit(0);
}
