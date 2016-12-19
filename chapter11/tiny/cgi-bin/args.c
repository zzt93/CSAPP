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


void get_args(char **args, int n) {
    Method m = (Method) atoi(getenv(METHOD));
    switch (m) {
        case POST:

            break;
        case GET: {
            char *buf, *p;
            if ((buf = getenv("QUERY_STRING")) != NULL) {
                p = index(buf, '&');
                *p = '\0';
                strcpy(*args, buf);
                strcpy(*(++args), p + 1);
            }
        }
            break;
        default:
            assert(false);
    }
}
