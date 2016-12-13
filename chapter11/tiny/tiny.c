//
// Created by zzt on 12/12/16.
//


#include "../csapp.h"

void doit(int fd);


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
    }

    int port = atoi(argv[1]);
    int listenfd = Open_listenfd(port);
    int clientlen, connfd;
    struct sockaddr_in clientaddr;
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        doit(connfd);
        Close(connfd);
    }
}

