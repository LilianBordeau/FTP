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
        printf("server received %u bytes %s\n", (unsigned int)n, buf1);
        buf1[n-1] = 0;
        rio.rio_fd = open(buf1,O_RDONLY, "r");
        printf("ouverture fichier %d\n", rio.rio_fd);
        if(rio.rio_fd != -1){
          int lu = Rio_readnb(&rio,buf2,MAXBUF);
          if(lu > 0)
          {
            printf("taille fichier lu: %d\n", lu);
            fflush(stdout);
            Rio_writen(connfd, buf2, MAXBUF);
          }
        }
        else{
          printf("file not found\n");
          fflush(stdout);
        }

    }
    //Rio_writen(connfd, buf, MAXBUF);
}
