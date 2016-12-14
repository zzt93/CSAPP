//
// Created by zzt on 12/14/16.
//
#include <stdlib.h>
#include <string.h>
#include "../../csapp.h"


int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], content[MAXLINE];
    if ((buf = getenv("QUERY_STRING")) != NULL) {
        p = strchr(buf, '&');
        if (p != NULL) {
            *p = '\0';
        }
        strcpy(arg1, buf);
    }

    sprintf(content, "Welcome to Tiny: ");
    sprintf(content, "%sThe Internet echo portal. \r\n<p>", content);
    sprintf(content, "%sThe query is %s\r\n<p>",
            content, arg1);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    printf("Content-length: %d\r\n", (int) strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}