/*
 * echoclient.c - An echo client
 */
#include "csapp.h"
#include "echo.h"
#include <signal.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
    int clientfd, port;
    char *host, buf[MAXLINE], buf2[MAXLINE];
    rio_t rio;

    // if (argc != 3) {
    //     fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    //     exit(0);
    // }
    host = argv[1];
    port = 2121;

    /*
     * Note that the 'host' can be a name or an IP address.
     * If necessary, Open_clientfd will perform the name resolution
     * to obtain the IP address.
     */
    clientfd = Open_clientfd(host, port);

    /*
     * At this stage, the connection is established between the client
     * and the server OS ... but it is possible that the server application
     * has not yet called "Accept" for this connection
     */
    printf("client connected to server OS\n");

    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        if (Rio_readnb(&rio, buf2, MAXLINE) > 0) {
            // printf("%s\n", buf2);
            // fflush(stdout);
            buf[strlen(buf) - 1] = 0;
            int fd = open(buf, O_WRONLY|O_CREAT);
            Dup2(fd,1);
            Fputs(buf2, stdout);
        } else { /* the server has prematurely closed the connection */
            break;
        }
    }
    Close(clientfd);
    exit(0);
}
