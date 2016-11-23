//
// Created by zzt on 11/22/16.
//

#ifndef CSAPP_CLIENT_H
#define CSAPP_CLIENT_H

/**
 * Returns: descriptor if OK, −1 on Unix error, −2 on DNS error
 * @param hostname
 * @param port
 * @return
 */
int open_clientfd(char *hostname, int port);

#endif //CSAPP_CLIENT_H
