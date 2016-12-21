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


int get_args(char **args, int n) {
    Method m = (Method) atoi(getenv(METHOD));
    int count = 0;
    switch (m) {
        case POST:
//            read_request_body();
            break;
        case GET: {
            char *buf, *p;
            if ((buf = getenv("QUERY_STRING")) != NULL) {
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
            }
            break;
        }
        default:
            assert(false);
    }
    return count;
}
