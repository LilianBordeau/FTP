/*
 * echo - read and echo text lines until client closes connection
 */
#include "csapp.h"
#include "echo.h"

void echo(int connfd)
{
    size_t n;
    rio_t rio;
    char buf1[MAXLINE];
    char buf2[MAXBUF];

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf1, MAXLINE)) != 0) {
        buf1[n-1] = 0;
        printf("%u bytes received (%s).\n", (unsigned int)n, buf1);
        rio.rio_fd = open(buf1,O_RDONLY, "r");
        if(rio.rio_fd != -1){
          printf("Open file descriptor %d.\n", rio.rio_fd);
          int lu = Rio_readnb(&rio,buf2,MAXBUF);
          if(lu > 0)
          {
            printf("Read file of size %d.\n", lu);
            fflush(stdout);
            Rio_writen(connfd, buf2, MAXBUF);
          }
          else{
            printf("File is empty.\n");
            fflush(stdout);
          }
        }
        else{
          printf("File unfound.\n");
          fflush(stdout);
        }

    }
    //Rio_writen(connfd, buf, MAXBUF);
}
