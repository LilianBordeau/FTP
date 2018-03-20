/*
 * echo - read and echo text lines until client closes connection
 */
#include "csapp.h"
#include "echo.h"

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];

    rio_t rio;
    int fd;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
       printf("server received %u bytes\n", (unsigned int)n);
       // fd=open(buf,O_RDONLY, "r");
       // printf("j'ai ouvert le fichier");
       // Rio_readn(fd,buf,MAXLINE);
       // printf("j'ai lu le fichier");
       // Rio_writen(connfd, buf, n);
    }
}
