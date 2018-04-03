/*
 * echoclient.c - An echo client
 */
#include "csapp.h"
#include "echo.h"
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>


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

    // Mesure du temps
    struct timeval tv1,tv2;
    struct timezone tz;
    long long diff;

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




    printf("Connected to %s.\n", argv[1]);

    Rio_readinitb(&rio, clientfd);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        if (Rio_readnb(&rio, buf2, MAXLINE) > 0) {
            //printf("%s\n", buf2);
            //fflush(stdout);
            gettimeofday(&tv1,&tz); // Start
            buf[strlen(buf) - 1] = 0;

            int fd = open("recu", O_RDWR|O_CREAT, "w");
            int saved_stdout = dup(1);

            if(fd == -1)
            {
              printf("File cannot be created.\n");
            }
            Dup2(fd,1);
            Fputs(buf2, stdout);
            close(fd);

            Dup2(saved_stdout,1);
            gettimeofday(&tv2,&tz); // End
            printf("Transfer successfully complete.\n");
            // Duree
            diff=(tv2.tv_sec-tv1.tv_sec) * 1000L +  (tv2.tv_usec-tv1.tv_usec);
            printf("X bytes received in %lld microseconds (Z Kbytes/s).\n",diff);
            close(saved_stdout);

        } else {
            /* the server has prematurely closed the connection */
            printf("Connexion failure.\n");
            break;
        }
    }
    Close(clientfd);
    exit(0);
}
