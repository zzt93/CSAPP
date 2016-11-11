#include <stdio.h>
#include <stdlib.h>

void dd2hex(char *string);

void hex2dd(char *argv) {
    unsigned int ui = (unsigned int) strtol(argv, NULL, 16);
    printf("%u.%u.%u.%u\n", ui >> 24, (ui >> 16) & 0xff, (ui >> 8) & 0xff, ui & 0xff);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        puts("Usage: ./a.out -[h|d] [hex|dotted decimal]");
    }
    if (argv[1][1] == 'h') {
        hex2dd(argv[2]);
    } else if (argv[1][1] == 'd') {
        dd2hex(argv[2]);
    } else {
        puts("Usage: ./a.out -[h|d] [hex|dotted decimal]");
    }
}

void dd2hex(char *s) {
    char *ss[4];
    int i = 0;
    ss[i++] = s;
    while (*s != 0) {
        if (*s == '.') {
            ss[i++] = s + 1;
        }
        s++;
    }
    long ui = atol(ss[0]) << 24 |
            atol(ss[1]) << 16 | atol(ss[2]) << 8 | atol(ss[3]);
    printf("0x%x\n", (unsigned int) ui);
}