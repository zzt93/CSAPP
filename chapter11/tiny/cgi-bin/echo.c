//
// Created by zzt on 12/14/16.
//
#include <stdlib.h>
#include <string.h>
#include "tiny.h"


int main(void) {
    char *buf, *p;
    int len = 1;
    char arg[len][MAXLINE], content[MAXLINE];
    int c = get_args(arg, len);
    if (c != len) {
        exit(1);
    }

    sprintf(content, "Welcome to Tiny: ");
    sprintf(content, "%sThe Internet echo portal. \r\n<p>", content);
    sprintf(content, "%sThe query is %s\r\n<p>",
            content, arg[0]);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    printf("Content-length: %d\r\n", (int) strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}