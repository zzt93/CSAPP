//
// Created by zzt on 12/19/16.
//

#ifndef CSAPP_TINY_H
#define CSAPP_TINY_H

typedef enum {
    GET, HEAD, POST
} Method;

static char *const METHOD = "REQUEST_METHOD";

static char *const QUERY_STRING = "QUERY_STRING";

static char *const CONTENT_TYPE = "CONTENT_TYPE";

static char *const CONTENT_LEN = "CONTENT_LEN";

int get_args(char **args, int n);

#endif //CSAPP_TINY_H
