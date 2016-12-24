//
// Created by zzt on 12/19/16.
//


#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <strings.h>
#include <memory.h>
#include <stdio.h>
#include "tiny.h"


int getInt(char **args, int n, char *buf);

int get_args(char **args, int n) {
    Method m = (Method) atoi(getenv(METHOD));
    int count = 0;
    char *buf = NULL;
    switch (m) {
        case POST: {
            int len = 0;
            if ((getline(&buf, &len, stdin)) != -1) {
                count = getInt(args, n, buf);
            }
            break;
        }
        case GET: {
            if ((buf = getenv("QUERY_STRING")) != NULL) {
                count = getInt(args, n, buf);
            }
            break;
        }
        default:
            assert(false);
    }
    return count;
}

int getInt(char **args, int n, char *buf) {
    int count = 0;
    char *p;
    while ((p = index(buf, '&')) != NULL && count < n) {
        *p = '\0';
        strcpy(*args, buf);
        args++;
        buf = p + 1;
        count++;
    }
    if (count < n) {
        strcpy(*args, buf);
        count++;
    }
    return count;
}
