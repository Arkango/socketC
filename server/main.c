//
// Created by arcangelo on 10/7/19.
//
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define PORT 5000
#define BUFFERSIZE 1024
#define MAXCONN 6

void func(int sockfd);

int main(int argc,char const *argv[]) {
    int sock,connfd;
    char buff[BUFFERSIZE];
    struct sockaddr_in serv_addr,client;

    //creazione del socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
        printf("\n Socket creation error\n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(buff, '0', sizeof(buff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);

    bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Binding newly created socket to given IP and verification
    /*if ((bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("socket bind failed...\n");
        close(sock);
        exit(-1);
    }*/

    listen(sock, MAXCONN);

    /*if ((listen(sock, MAXCONN)) != 0) {
        printf("Listen failed...\n");
        close(sock);
        exit(-1);
    }*/

    int flag =0;
    int len = sizeof(client);




        int times = 1;
        ssize_t numBytesRcvd;

       /* while(1){

          if(times == 0) {
              char *ok_connect = "connessione avvenuta";
              int connectLenght = sizeof(ok_connect);
              if (send(connfd, ok_connect, connectLenght, 0) != connectLenght) {
                  printf("send() sent a different number of bytes than expected\n");
                  close(sock);
                  close(connfd);
                  exit(-1);
              }
          }



            numBytesRcvd = recv(connfd,buff,BUFFERSIZE-1,0);
            buff[numBytesRcvd] = '\0';
            if(numBytesRcvd <= 0){
                printf("Connection failed or closed prematurely,Exit...\n");
                flag = 1;
                break;
            }

            times += 1;
            if (times == 1) {

                char *newString;
                int i=0;
                for(i=0; i < numBytesRcvd; i++){
                    newString += toupper(buff[i]);
                }

                if (send(sock, newString, strlen(buff), 0) !=  strlen(buff)) {
                    printf("send() sent a different number of bytes than expected\n");
                    flag = 1;
                    break;
                }



            }else if(times == 2){

                char *newString;
                int i=0;
                for(i=0; i < numBytesRcvd; i++){
                    newString += tolower(buff[i]);
                }

                if (send(sock, newString, strlen(buff), 0) !=  strlen(buff)) {
                    printf("send() sent a different number of bytes than expected\n");
                    flag = 1;
                    break;
                }

            }

        }*/

    connfd = accept(sock, (struct sockaddr*)&client, &len);
    func(connfd);



    close(sock);
    if(flag == 1){
        return -1;
    }


    return 0;
}

void func(int sockfd)
{
    char buff[BUFFERSIZE];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, BUFFERSIZE);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, BUFFERSIZE);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}