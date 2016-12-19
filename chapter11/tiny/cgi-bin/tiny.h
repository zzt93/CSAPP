//
// Created by zzt on 12/19/16.
//

#ifndef CSAPP_TINY_H
#define CSAPP_TINY_H

typedef enum {
    GET, HEAD, POST
} Method;

static char *const METHOD = "METHOD";

void get_args(char **args, int n);

#endif //CSAPP_TINY_H
