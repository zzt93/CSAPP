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

#define CONTENT_TYPE "Content-Type"
#define CONTENT_LEN "Content-Length"

static char *headers[] = {CONTENT_LEN, CONTENT_TYPE};

#include "../../csapp.h"

int get_args(char args[][MAXLINE], int n);


#endif //CSAPP_TINY_H
