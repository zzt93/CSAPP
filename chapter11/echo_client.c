//
// Created by zzt on 11/22/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

#define MAX 1024

int main(int argc, char **argv) {
    int clientfd, port;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    char *host = argv[1];
    port = atoi(argv[2]);

    if ((clientfd = open_clientfd(host, port)) < 0) {
        exit(0);
    }
    rio_t rio;
    rio_readinitb(&rio, clientfd);

    char line[MAX];
    while (fgets(line, MAX, stdin) != NULL) {
        
    }
}
