/*
 * echoserveri.c - An iterative echo server
 */

#include "csapp.h"
#include "echo.h"
#include <signal.h>
#include <sys/wait.h>

#define MAX_NAME_LEN 256
#define NPROC 10

pid_t procIDs[NPROC];
void get_file(int connfd);

void echo(int connfd);

/*
 * Note that this code only works with IPv4 addresses
 * (IPv6 is not supported)
 */

 void handler(int sig)
 {
     pid_t pid;
     while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
     return;

 }

 void createProcesses(){
        int i=0;
        while(i<NPROC){

          procIDs[i] = fork();
          if(procIDs[i] < 0 ){
              perror("Fork error!");
          }else if(procIDs[i] == 0){
            return;
          }
          i++;
        }
    }


int main(int argc, char **argv)
{

    signal(SIGCHLD, handler);


    int listenfd, connfd, port;
    socklen_t clientlen;
    struct sockaddr_in clientaddr;
    char client_ip_string[INET_ADDRSTRLEN];
    char client_hostname[MAX_NAME_LEN];

    // if (argc != 2) {
    //     fprintf(stderr, "usage: %s <port>\n", argv[0]);
    //     exit(0);
    // }
    port = 2121;

    clientlen = (socklen_t)sizeof(clientaddr);

    listenfd = Open_listenfd(port);

    createProcesses();
    while (1) {

        while((connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen))<0);

          /* determine the name of the client */
          Getnameinfo((SA *) &clientaddr, clientlen,
                      client_hostname, MAX_NAME_LEN, 0, 0, 0);

          /* determine the textual representation of the client's IP address */
          Inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip_string,
                    INET_ADDRSTRLEN);

          printf("Connected to %s (%s)\n", client_hostname,
                 client_ip_string);

          echo(connfd);
          //get_file(connfd);
          Close(connfd);
          //exit(0);


    }
    exit(0);
}
