//
// Created by zzt on 11/21/16.
//

#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <strings.h>
#include <network.h>


int open_clientfd(char *hostname, int port) {
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    if((hp = gethostbyname(hostname)) == NULL) {
        return -2;
    }

    bzero((char *) &serveraddr, sizeof serveraddr);
    serveraddr.sin_family = AF_INET;
    bcopy((char *) hp->h_addr_list[0],
          (char *) &serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);

    if (connect(clientfd, (SA *) &serveraddr, sizeof serveraddr) < 0) {
        return -1;
    }
    return clientfd;
}
