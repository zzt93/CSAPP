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

int copy_args(char args[][MAXLINE], int n, char *buf);

int get_args(char args[][MAXLINE], int n) {
    Method m = (Method) atoi(getenv(METHOD));
    int count = 0;
    char *buf = NULL;
    switch (m) {
        case POST: {
            size_t len = 0;
            if ((getline(&buf, &len, stdin)) != -1) {
                count = copy_args(args, n, buf);
            }
            free(buf);
            break;
        }
        case GET: {
            if ((buf = getenv(QUERY_STRING)) != NULL) {
                count = copy_args(args, n, buf);
            }
            break;
        }
        default:
            assert(false);
    }
    return count;
}

int copy_args(char args[][MAXLINE], int n, char *a) {
    size_t len = strlen(a);
    if (len == 0) {
        return 0;
    }
    char *buf = malloc(len + 1);
    strcpy(buf, a);

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

//#ifdef test

int main() {
    char me[4];
    sprintf(me, "%d", GET);
    setenv(METHOD, me, 1);
    int len = 32;
    char *args[] = {"", "a=1", "a=1&b=23", "f=1&c=3&d=3"};
    for (int i = 0; i < sizeof args / sizeof args[0]; ++i) {
        setenv(QUERY_STRING, args[i], 1);
        char res[len][MAXLINE];
        int count = get_args(res, len);
        assert(count == i);
    }
//    sprintf(me, "%d", POST);
//    setenv(METHOD, me, 1);
//    char args2[] = ;
//    fputs(args2, stdin);
//    count = get_args(res, len);
//    assert(count == 3);
}
//#endif