//
// Created by zzt on 12/12/16.
//


#include "../csapp.h"
#include "cgi-bin/tiny.h"

void doit(int fd);


void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

void read_requesthdrs(rio_t *ptr);

int parse_uri(char *uri, char *filename, char *cgiargs);

void serve_static(int fd, char *filename, __off_t size, Method m);

void server_dynamic(int fd, char *filename, char *cgiargs, Method m);

void get_filetype(char *filename, char *filetype);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
    }

    int port = atoi(argv[1]);
    int listenfd = Open_listenfd(port);
    int clientlen, connfd;
    struct sockaddr_in clientaddr;
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        doit(connfd);
        Close(connfd);
    }
}

void doit(int fd) {
    int is_static;
    rio_t rio;;

    /* read request line and headers*/
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);
    printf("%s\n", buf);
    Method m = GET;
    if (strcasecmp(method, "HEAD") == 0) {
        m = HEAD;
    } else if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }
    read_requesthdrs(&rio);

    char filename[MAXLINE], cgiargs[MAXLINE];
    /* parse URI from GET request*/
    is_static = parse_uri(uri, filename, cgiargs);
    struct stat sbuf;
    if (stat(filename, &sbuf) < 0) {
        clienterror(fd, filename, "404", "Not Found",
                    "Tiny couldn't find this file");
    }

    if (is_static) {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't read the file");
            return;
        }
        serve_static(fd, filename, sbuf.st_size, m);
    } else {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't run the CGI program");
            return;
        }
        server_dynamic(fd, filename, cgiargs, m);
    }
}

void server_dynamic(int fd, char *filename, char *cgiargs, Method m) {
    char buf[MAXLINE], *emptylist[] = {NULL};

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    Rio_writen(fd, buf, strlen(buf));
    switch (m) {
        case HEAD:
            return;
        case GET:
            setenv("QUERY_STRING", cgiargs, 1);
            break;
        case POST:
            Dup2(fd, STDIN_FILENO);;
    }
    if (Fork() == 0) {
        /* Real server would set all CGI vars here */
        char me[4];
        sprintf(me, "%d", m);
        setenv(METHOD, me, 1);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    wait(NULL);
}

void serve_static(int fd, char *filename, __off_t size, Method m) {
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];

    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, size);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);
    Rio_writen(fd, buf, strlen(buf));
    switch (m) {
        case HEAD:
            return;
        case GET:
            break;
        case POST:;
    }
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(0, size, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, size);
    Munmap(srcp, size);
}

void get_filetype(char *filename, char *filetype) {
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mp4"))
        strcpy(filetype, "video/mpeg");
    else if (strstr(filename, ".css"))
        strcpy(filetype, "text/css");
    else
        strcpy(filetype, "text/plain");
}

int parse_uri(char *uri, char *filename, char *cgiargs) {
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri) - 1] == '/') {
            strcat(filename, "home.html");
        }
        return 1;
    } else {
        ptr = index(uri, '?');
        if (ptr) {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        } else {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
    }
    return 0;
}

void read_requesthdrs(rio_t *ptr) {
    char buf[MAXLINE];

    Rio_readlineb(ptr, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        Rio_readlineb(ptr, buf, MAXLINE);
        printf("%s", buf);
    }
}

void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
    char buf[MAXLINE], body[MAXBUF];

    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int) strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
