//
// Created by zzt on 12/27/16.
//


#include "tiny.h"

int main(void) {
    int len = 2;
    char args[len][MAXLINE], content[MAXLINE];
    int count = get_args(args, len);
    int n1 = 0, n2 = 0;
    if (count == len) {
        // ignore name, just keep value
        char *v1 = index(args[0], '=') + 1;
        char *v2 = index(args[1], '=') + 1;

        n1 = atoi(v1);
        n2 = atoi(v2);
    } else {
        exit(1);
    }

    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sThe Internet addition portal. \r\n<p>", content);
    sprintf(content, "%sThe answer is %d + %d = %d\r\n<p>",
            content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}